package edu.umsl;

import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        final Hydra hydra = new Hydra(Hydra.createHydraParts(getHeadCount(), getTailCount()));
        final PyPy pypy = new PyPy(hydra);

        Scanner in = new Scanner(System.in);
        while(true) {
            // exit condition
            if (hydra.getHeadCount() == 0 && hydra.getTailCount() == 0) {
                println("");
                println("Hooray! PyPy defeated the Hydra!");
                System.exit(0);
            }

            // print instructions
            println("");
            println("Enter [0-3] to attack, [q] to quit, [S] to see current minimum # of moves to defeat the Hydra");
            println("[0] CutOffOneHead, [1] CutOffTwoHeads, [2] CutOffOneTail, [3] CutOffTwoTails");
            println("Head Count: " + hydra.getHeadCount() + " Tail Count: " + hydra.getTailCount());

            // get input
            String userInput = in.nextLine();
            if (getValidInputs(pypy).contains(userInput)) {
                // valid input. safe to use
                if (pypy.getPossibleMoves().contains(userInput)) {
                    // valid attack. safe to test
                    if (pypy.validMove(PyPyMove.values()[Integer.parseInt(userInput)])) {
                        // valid attack. safe to use
                        pypy.takeTurn(PyPyMove.values()[Integer.parseInt(userInput)]);
                    } else {
                        // invalid attack.
                        println("The Hydra can not have negative parts");
                    }
                } else if (userInput.equals("q")) {
                    // quit
                    println("PyPy fled from battle and is traveling home with their head hung in defeat");
                    break;
                } else if (userInput.equals("S")) {
                    // get shortest path to win
                    println("-1 means the Hydra is undefeatable");
                    println("The shortest number of moves possible to defeat the Hydra is "
                            + HydraSolver.solveHydra(hydra.getHeadCount(), hydra.getTailCount()));
                }

            } else {
                // invalid input
                println(userInput + " is not valid input");
            }
        }
    }

    private static ArrayList<String> getValidInputs(PyPy pypy) {
        ArrayList<String> validInputs = new ArrayList<>(pypy.getPossibleMoves()); // construct with possible moves
        validInputs.add("S"); // Show shortest path to victory. -1 if impossible
        validInputs.add("q"); // quit
        return validInputs;
    }

    private static int getTailCount() {
        int tailCount;
        Scanner in = new Scanner(System.in);
        while(true) {
            try {
                println("Enter a tail count for the Hydra:");
                tailCount = Integer.parseInt(in.nextLine().trim());

                if (tailCount < 0) {
                    println("You must enter a positive integer. Try again");
                    continue;
                }
                break;
            } catch (NumberFormatException e) {
                println("You must enter a positive integer. Try again");
            }
        }
        return tailCount;
    }

    private static int getHeadCount() {
        int headCount;
        Scanner in = new Scanner(System.in);
        while(true) {
            try {
                println("Enter a head count for the Hydra:");
                headCount = Integer.parseInt(in.nextLine().trim());

                if (headCount < 0) {
                    println("You must enter a positive integer. Try again");
                    continue;
                }
                break;
            } catch (NumberFormatException e) {
                println("You must enter a positive integer. Try again");
            }
        }
        return headCount;
    }


    // Alias for System.out.println
    private static void println(Object object) {
        System.out.println(object);
    }
}
