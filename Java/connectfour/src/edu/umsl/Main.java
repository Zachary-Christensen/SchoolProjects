package edu.umsl;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        GamePiece[][] gamePieces = GamePiece.createGamePieceArray(6, 7); // gamePieces[row][column]
        GameManager gameManager = new GameManager(gamePieces);

        Player player1;
        Player player2;

        Scanner in = new Scanner(System.in);

        System.out.println("Would Player 1 like to be Red or Yellow?");
        if (in.nextLine().trim().toUpperCase().startsWith("R")) {
            player1 = new Player(new PhysicalTakeTurnBehavior(gameManager), ColorType.RED);
            player2 = new Player(new PhysicalTakeTurnBehavior(gameManager), ColorType.YELLOW);
        }
        else {
            player1 = new Player(new PhysicalTakeTurnBehavior(gameManager), ColorType.YELLOW);
            player2 = new Player(new PhysicalTakeTurnBehavior(gameManager), ColorType.RED);
        }
        System.out.println("Player 1 is " + player1.getColorType().toString() + " and Player 2 is " + player2.getColorType().toString());

        System.out.println("Player 1 goes first");
        System.out.println("Enter a number 0-" + (gamePieces[0].length - 1));
        gameManager.printGameBoard();

        boolean player1sTurn = true;
        while(true) {
            if (player1sTurn) {
                System.out.println("Player 1's turn");
                player1.executeTakeTurnBehavior();
            }
            else {
                System.out.println("Player 2's turn");
                player2.executeTakeTurnBehavior();
            }
            gameManager.printGameBoard();

            if (gameManager.checkWinFromRowAndColumn(gameManager.getLastTurnRow(), gameManager.getLastTurnColumn())) {
                System.out.println(
                        (player1sTurn ? player1.getColorType().toString() : player2.getColorType().toString()) + " won!");
                break;
            }
            else if (gameManager.checkDraw()) {
                System.out.println("There has been a draw");
                break;
            }
            else {
                System.out.println("Continue");
            }
            player1sTurn = !player1sTurn;
        }
        System.out.println("Good game");
    }
}
