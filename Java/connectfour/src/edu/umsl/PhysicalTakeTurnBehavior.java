package edu.umsl;

import java.util.Scanner;

public class PhysicalTakeTurnBehavior implements ITakeTurnBehavior {

    private final GameManager gameManager;

    public PhysicalTakeTurnBehavior(
            GameManager gameManager
    ) {
        this.gameManager = gameManager;
    }

    @Override
    public void takeTurn(ColorType colorType) {
        Scanner in = new Scanner(System.in);
        while (true) {
            try {
                int columnIn = Integer.parseInt(in.nextLine().trim());
                while (true) {
                    if (!gameManager.validColumn(columnIn)) {
                        System.out.println("Invalid column, try again");
                        columnIn = Integer.parseInt(in.nextLine().trim());
                    }
                    else {
                        break;
                    }
                }
                gameManager.executeTurn(colorType, columnIn);
                break;
            } catch (NumberFormatException e) {
                System.out.println("You must input a number, try again");
            } catch (Exception e) {
                System.out.println("Something happened");
                break;
            }
        }
    }
}
