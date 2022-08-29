import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.IOException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static java.lang.Thread.sleep;

/*
    Searches through either random or linked wikipedia pages and totals word counts from innerHTML
 */
public class WebCrawler {

    public static void main(String[] args) {
        try {
            long startTime = System.currentTimeMillis();

            HashSet<String> pageTitles = new HashSet<>();
            HashMap<String, Integer> wordCount = new HashMap<>();
            int numberOfPages = 1000; // try 10 pages

//            crawlRelatedWikipediaPages(pageTitles, wordCount, numberOfPages, getRandomWikipediaDoc());//Jsoup.connect("https://en.wikipedia.org/wiki/Guitar").get());
            crawlRandomWikipediaPages(pageTitles, wordCount, numberOfPages);

            wordCount = sortByValue(wordCount, true);
            System.out.println("\nWord Counts:\n\nCount: word");
            wordCount.forEach((key,value) -> System.out.println(value.toString() + ": " + key));

            System.out.println("\nRuntime: " + (System.currentTimeMillis() - startTime) + "ms");

        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    // crawl related wikipedia pages and count the number of distinct words separated by spaces
    private static void crawlRelatedWikipediaPages(HashSet<String> pageTitles, HashMap<String, Integer> wordCount, int numberOfPages, Document startingPage) throws IOException, InterruptedException {
        Elements links = filterWikipediaLinks(startingPage.select("a[href]"));
        // remove extra links randomly until right size
        while (links.size() > numberOfPages) {
            links.remove(new Random().nextInt(links.size() - 1));
        }
        // add distinct links from a random link in links until right size
        while ((long) links.size() < numberOfPages) {
            Element link = links.get(new Random().nextInt(links.size() - 1));
            Document doc = Jsoup.connect(link.attr("abs:href")).get();
            Elements tempLinks = filterWikipediaLinks(doc.select("a[href]"));
            for (Element tempLink : tempLinks) {
                if (links.stream().noneMatch(x -> x.attr("abs:href").equals(tempLink.attr("abs:href")))) {
                    links.add(tempLink);
                }
            }
            sleep(100L);
        }
        System.out.println("Page Titles:\n");
        // count words and store titles for each link
        for (Element link : links) {
            Document doc = Jsoup.connect(link.attr("abs:href")).get();
            updateTitleAndWordCountFromDocument(pageTitles, wordCount, doc);

            sleep(100L);
        }
    }

    // crawl random wikipedia pages and count the number of distinct words separated by spaces
    private static void crawlRandomWikipediaPages(HashSet<String> pageTitles, Map<String, Integer> wordCount, int numberOfPages) throws IOException, InterruptedException {
        System.out.println("Page Titles:\n");
        for (int i = 0; i < numberOfPages; i++) {
            Document doc = getRandomWikipediaDoc();
            updateTitleAndWordCountFromDocument(pageTitles, wordCount, doc);

            sleep(100L);
        }
    }

    // iterates document and increment distinct word counts separated by spaces
    private static void updateTitleAndWordCountFromDocument(HashSet<String> pageTitles, Map<String, Integer> wordCount, Document doc) {
        String title = doc.title().split("[-]")[0].trim();
        System.out.println(title);
        pageTitles.add(title);

        Elements elements = doc.getAllElements();
        for (Element element : elements) {
            String[] words = element.text().trim().split("\\s+");
            for (String word : words) {
                wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
            }
        }
    }

    private static Document getRandomWikipediaDoc() throws IOException {
        // special url from wikipedia that returns a random article
        return Jsoup.connect("https://en.wikipedia.org/wiki/Special:Random").get();
    }

    // filters links taken from a wikipedia article to only other articles
    private static Elements filterWikipediaLinks(Elements links) {
        Elements filteredLinks = new Elements();
        // regex: rejectThisOne|alsoThisOne|andThisOne|(?<groupName>acceptThisOne)
        String pattern = ".*/wiki/Main_Page|.*/wiki/Wikidata|(?<valid>https://en\\.wikipedia\\.org/wiki/[A-Za-z0-9_]+)";
        Pattern r = Pattern.compile(pattern);
        for (Element link : links) {
            Matcher m = r.matcher(link.attr("abs:href"));
            if (m.find()) {
                if (m.group("valid") != null) {
                    if (m.group("valid").equals(link.attr("abs:href"))
                            && filteredLinks.stream().noneMatch(x -> x.attr("abs:href").equals(link.attr("abs:href")))) {
//                        System.out.println("link: " + link.attr("abs:href"));
                        filteredLinks.add(link);
                    }
                }
            }
        }
        return filteredLinks;
    }

    // altered from https://www.geeksforgeeks.org/sorting-a-hashmap-according-to-values/
    // function to sort hashmap by values
    public static HashMap<String, Integer> sortByValue(HashMap<String, Integer> hm, boolean asc)
    {
        // Create a list from elements of HashMap
        List<Map.Entry<String, Integer> > list = new LinkedList<>(hm.entrySet());

        // Sort the list
        if (asc) {
            list.sort(Comparator.comparing(Map.Entry::getValue)); // ascending order
        } else {
            list.sort((o1, o2) -> (o2.getValue()).compareTo(o1.getValue())); // descending order
        }

        // put data from sorted list to hashmap
        HashMap<String, Integer> temp = new LinkedHashMap<>();
        for (Map.Entry<String, Integer> aa : list) {
            temp.put(aa.getKey(), aa.getValue());
        }
        return temp;
    }
}
