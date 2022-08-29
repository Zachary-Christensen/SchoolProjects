package edu.umsl;

import java.util.concurrent.TimeUnit;

public class RobotTakeTurnBehavior implements ITakeTurnBehavior {

    private final GameManager gameManager;

    public RobotTakeTurnBehavior(
            GameManager gameManager
    ) {
        this.gameManager = gameManager;
    }

    @Override
    public void takeTurn(ColorType colorType) {
//        try {
//            TimeUnit.MILLISECONDS.sleep(900L);
//            System.out.println("\nI'm thinking");
//            TimeUnit.MILLISECONDS.sleep(900L);
//            System.out.println("...");
//            TimeUnit.MILLISECONDS.sleep(700L);
//            System.out.println("...");
//            TimeUnit.MILLISECONDS.sleep(700L);
//            System.out.println("...");
//            TimeUnit.MILLISECONDS.sleep(600L);
//        } catch (InterruptedException e) {
//            // this is just for effect, if error continue
//        }

        int randomColumn = getRandomColumn();
        while(!gameManager.validColumn(randomColumn)) {
            randomColumn = getRandomColumn();
        }
        gameManager.executeTurn(colorType, randomColumn);
    }

    private int getRandomColumn() {
        // returns random integer from 0-6
        return (int)Math.round(Math.random() * 6f);
    }
}
