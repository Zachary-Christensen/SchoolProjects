package edu.umsl;

import java.util.ArrayList;

public class PyPy {

    private final Hydra hydra;

    public PyPy(Hydra hydra) {
        this.hydra = hydra;
    }

    public boolean validMove(PyPyMove pyPyMove) {
        switch (pyPyMove) {
            case CutOffOneHead -> {
                return hydra.getHeadCount() - 1 >= 0;
            }
            case CutOffTwoHeads -> {
                return hydra.getHeadCount() - 2 >= 0;
            }
            case CutOffOneTail -> {
                return hydra.getTailCount() - 1 >= 0;
            }
            case CutOffTwoTails -> {
                return hydra.getTailCount() - 2 >= 0;
            }
        }
        return false;
    }

    public ArrayList<String> getPossibleMoves() {
        ArrayList<String> moves = new ArrayList<>();
        for (PyPyMove move : PyPyMove.values()) {
            moves.add(String.valueOf(move.ordinal()));
        }
        return moves;
    }

    public void takeTurn(PyPyMove pyPyMove) {
        switch (pyPyMove) {
            case CutOffOneHead -> {
                System.out.println("PyPy cut off one head!");
                hydra.damage(HydraPart.H, 1);
            }
            case CutOffTwoHeads -> {
                System.out.println("PyPy cut off two heads!");
                hydra.damage(HydraPart.H, 2);
            }
            case CutOffOneTail -> {
                System.out.println("PyPy cut off one tail!");
                hydra.damage(HydraPart.T, 1);
            }
            case CutOffTwoTails -> {
                System.out.println("PyPy cut off two tails!");
                hydra.damage(HydraPart.T, 2);
            }
        }
    }
}
