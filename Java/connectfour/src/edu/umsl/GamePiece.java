package edu.umsl;

public class GamePiece {
    private ColorType colorType = ColorType.EMPTY;

    private final int topBound;
    private final int bottomBound;
    private final int rightBound;
    private final int leftBound;

    public GamePiece(
            int topBound,
            int bottomBound,
            int rightBound,
            int leftBound
    ) {
        this.topBound = topBound;
        this.bottomBound = bottomBound;
        this.rightBound = rightBound;
        this.leftBound = leftBound;
    }

    public ColorType getColorType() {
        return colorType;
    }

    public int getTopBound() {
        return topBound;
    }

    public int getBottomBound() {
        return bottomBound;
    }

    public int getLeftBound() {
        return leftBound;
    }

    public int getRightBound() {
        return rightBound;
    }

    public void setColorType(ColorType colorType) {
        // Only settable from empty
        if (this.colorType == ColorType.EMPTY) {
            this.colorType = colorType;
        }
    }

    public String getColorSymbol() {
        if (colorType == ColorType.EMPTY)
            return " ";
        else
            return colorType.toString().substring(0, 1);
    }

    public static GamePiece[][] createGamePieceArray(int rowCount, int columnCount) {
        GamePiece[][] gamePieces = new GamePiece[rowCount][columnCount];
        for (int row = 0; row < rowCount; row++) {
            for (int column = 0; column < columnCount; column++) {
                gamePieces[row][column] = new GamePiece(
                                Math.min(rowCount - row - 1, 3),       // topBound
                                Math.min(row, 3),                      // bottomBound
                                Math.min(columnCount - column - 1, 3), // rightBound
                                Math.min(column, 3)                    // leftBound
                );
            }
        }
        return gamePieces;
    }
}
