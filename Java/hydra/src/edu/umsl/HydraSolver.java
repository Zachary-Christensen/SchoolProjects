package edu.umsl;

public class HydraSolver {

    public static long solveHydra(final long headCount, long tailCount) {
        if (tailCount == 0) {
            if (isEven(headCount)) {
                return headCount / 2;
            } else {
                return -1;
            }
        } else {
            int counter = 0;
            while (isOdd(tailCount) // loop if is still odd
                    || isOdd(tailCount / 2) && isEven(headCount)  // loop if even heads and odd # of moves to remove even # of tails
                    || isEven(tailCount / 2) && isOdd(headCount)) { // loop if odd heads and even # of moves to remove even # of tails
                tailCount++;
                counter++;
            }
            return counter // number of one tail chops
                    + (headCount + tailCount / 2) / 2 // number of two head chops
                    + tailCount / 2; // number of two tail chops
        }
    }

    private static boolean isEven(long number) {
        return number % 2 == 0;
    }
    private static boolean isOdd(long number) {
        return number % 2 != 0;
    }
}
