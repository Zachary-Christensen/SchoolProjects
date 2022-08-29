package edu.umsl;

import java.util.ArrayList;

public class Hydra {

    private final ArrayList<HydraPart> hydraParts;

    public Hydra(ArrayList<HydraPart> hydraParts) {
        this.hydraParts = hydraParts;
    }

    public ArrayList<HydraPart> getHydraParts() {
        return hydraParts;
    }

    public long getHeadCount() {
        return getHydraParts().stream().filter(x -> x.equals(HydraPart.H)).count();
    }

    public long getTailCount() {
        return getHydraParts().stream().filter(x -> x.equals(HydraPart.T)).count();
    }

    private void removeHydraPart(HydraPart hydraPart, int count) {
        while(count-- > 0) {
            getHydraParts().remove(hydraPart);
        }
    }

    private void addHydraPart(HydraPart hydraPart, int count) {
        while (count-- > 0) {
            getHydraParts().add(hydraPart);
        }
    }

    public void damage(HydraPart hydraPart, int count) {
        removeHydraPart(hydraPart, count);
        reactToDamage(hydraPart, count);
    }

    private void reactToDamage(HydraPart hydraPart, int count) {
        int hydraPartCount = 0;
        HydraPart hydraPartToAdd = null;
        switch (hydraPart) {
            case H -> {
                switch (count) {
                   case 1 -> {
                       hydraPartCount = 1;
                       hydraPartToAdd = HydraPart.H;
                       System.out.println("The Hydra grew another head!");
                   }
                   case 2 -> {
                       System.out.println("The Hydra is dazed with no reaction");
                       return;
                   }
                }
            }
            case T -> {
                switch (count) {
                    case 1 -> {
                        System.out.println("The Hydra grew two tails!");
                        hydraPartCount = 2;
                        hydraPartToAdd = HydraPart.T;
                    }
                    case 2 -> {
                        System.out.println("The Hydra grew another head!");
                        hydraPartCount = 1;
                        hydraPartToAdd = HydraPart.H;
                    }
                }
            }
        }
        addHydraPart(hydraPartToAdd, hydraPartCount);
    }

    // creation methods
    public static ArrayList<HydraPart> createHydraParts(int headCount, int tailCount) {
        ArrayList<HydraPart> hydraParts = new ArrayList<>();
        while(headCount-- > 0) {
            hydraParts.add(HydraPart.H);
        }
        while(tailCount-- > 0) {
            hydraParts.add(HydraPart.T);
        }
        return hydraParts;
    }
}
