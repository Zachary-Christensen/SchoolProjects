package edu.umsl;

import java.util.Arrays;

public class GameManager {

    private final GamePiece[][] gamePieces; // GamePiece[row][column]
    private int lastTurnRow;
    private int lastTurnColumn;

    public GameManager(
            GamePiece[][] gamePieces
    ) {
        this.gamePieces = gamePieces; // [6][7] instantiated with all empty pieces
    }

    public int getLastTurnRow() {
        return lastTurnRow;
    }

    public int getLastTurnColumn() {
        return lastTurnColumn;
    }

    private void setLastTurnRowAndColumn(int row, int column) {
        lastTurnRow = row;
        lastTurnColumn = column;
    }

    public void executeTurn(ColorType colorType, int column) {
        if (validColumn(column)) {
            // store last columns so we can use them to check if it was a winning turn
            setLastTurnRowAndColumn(getFirstEmptyRowInColumn(column), column);

            gamePieces[getFirstEmptyRowInColumn(column)][column].setColorType(colorType);
            return;
        }
        System.out.println("You can't move there, try again");
    }

    private int getFirstEmptyRowInColumn(int column) {
        for (int row = 0; row < gamePieces.length; row++) {
            if (gamePieces[row][column].getColorType() == ColorType.EMPTY) {
                return row;
            }
        }
        // Will make it to here if the row is full, however the 0 will make the validation fail
        // and protect against a bad move because index 0 can't be empty
        return 0;
    }

    public boolean validColumn(int column) {
        // check if is within bounds of array
        if (column < gamePieces[0].length && column >= 0) {
            // check that there is an empty spot in this column
            return gamePieces[getFirstEmptyRowInColumn(column)][column].getColorType() == ColorType.EMPTY;
        }
        return false;
    }

    public boolean checkDraw() {
        return Arrays.stream(gamePieces).noneMatch(x -> Arrays.stream(x).anyMatch(y -> y.getColorType() == ColorType.EMPTY));
    }

    public boolean checkWinFromRowAndColumn(int row, int column) {
        if (gamePieces[row][column].getColorType() != ColorType.EMPTY) {

            final int leftBound = gamePieces[row][column].getLeftBound();
            final int rightBound = gamePieces[row][column].getRightBound();
            final int topBound = gamePieces[row][column].getTopBound();
            final int bottomBound = gamePieces[row][column].getBottomBound();

            return checkHorizontalWin(row, column, leftBound, rightBound)
                    || checkVerticalWin(row, column, topBound, bottomBound)
                    || checkDiagonalUpWin(row, column, leftBound, rightBound, topBound, bottomBound)
                    || checkDiagonalDownWin(row, column, leftBound, rightBound, topBound, bottomBound);
        }
        return false;
    }

    private boolean checkDiagonalDownWin(int row, int column, int leftBound, int rightBound, int topBound, int bottomBound) {
        // check diagonal down win
        // diagonal win is not possible if there is not 3 spaces both horizontal and vertical around the gamePiece
        if (Math.abs(Math.min(leftBound, topBound) + Math.min(rightBound, bottomBound)) >= 3) {
            for (int i = -1 * Math.min(leftBound, topBound);
                 i <= Math.min(rightBound, bottomBound) - 3; i++) {
                if (Arrays.stream(new ColorType[] {
                        gamePieces[row - i][column + i].getColorType(),
                        gamePieces[row - i - 1][column + i + 1].getColorType(),
                        gamePieces[row - i - 2][column + i + 2].getColorType(),
                        gamePieces[row - i - 3][column + i + 3].getColorType()
                }).allMatch(x -> x == gamePieces[row][column].getColorType())) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean checkDiagonalUpWin(int row, int column, int leftBound, int rightBound, int topBound, int bottomBound) {
        // check diagonal up win
        // diagonal win is not possible if there is not 3 spaces both horizontal and vertical around the gamePiece
        if (Math.abs(Math.min(leftBound, bottomBound) + Math.min(rightBound, topBound)) >= 3) {
            for (int i = -1 * Math.min(leftBound, bottomBound); i <= Math.min(rightBound, topBound) - 3; i++) {
                if (Arrays.stream(new ColorType[] {
                        gamePieces[row + i][column + i].getColorType(),
                        gamePieces[row + i + 1][column + i + 1].getColorType(),
                        gamePieces[row + i + 2][column + i + 2].getColorType(),
                        gamePieces[row + i + 3][column + i + 3].getColorType()
                }).allMatch(x -> x == gamePieces[row][column].getColorType())) {
                    return true;
                }
            }
        }
        return false;
    }

    private boolean checkVerticalWin(int row, int column, int topBound, int bottomBound) {
        for (int i = -1 * bottomBound; i <= topBound - 3; i++) {
            if (Arrays.stream(new ColorType[] {
                    gamePieces[row + i][column].getColorType(),
                    gamePieces[row + i + 1][column].getColorType(),
                    gamePieces[row + i + 2][column].getColorType(),
                    gamePieces[row + i + 3][column].getColorType()
            }).allMatch(x -> x == gamePieces[row][column].getColorType())) {
                return true;
            }
        }
        return false;
    }

    private boolean checkHorizontalWin(int row, int column, int leftBound, int rightBound) {
        /*
             check horizontal win
             use bounds to choose starting and ending index for sets of 4 to check
             to see why i is negative and stops after it's <= 3 from the right bound
             check out the image in the WrittenWork folder
            */
        for (int i = -1 * leftBound; i <= rightBound - 3; i++) {
            if (Arrays.stream(new ColorType[] {
                    gamePieces[row][column + i].getColorType(),
                    gamePieces[row][column + i + 1].getColorType(),
                    gamePieces[row][column + i + 2].getColorType(),
                    gamePieces[row][column + i + 3].getColorType()
            }).allMatch(x -> x == gamePieces[row][column].getColorType())) {
                return true;
            }
        }
        return false;
    }

    public void printGameBoard() {
        // first index in the array is the bottom row
        // we want to print from top to bottom
        for (int row = gamePieces.length - 1; row >= 0; row--) {
            print("|");
            for (int column = 0; column < gamePieces[row].length; column++) {
                print(gamePieces[row][column].getColorSymbol() + "|");
            }
            print("\n");
        }

        // print column numbers underneath gameBoard
        print(" ");
        for (int column = 0; column < gamePieces[0].length; column++) {
            print(column + " ");
        }
        print("\n");
    }

    private void print(String string) {
        System.out.print(string);
    }
}


