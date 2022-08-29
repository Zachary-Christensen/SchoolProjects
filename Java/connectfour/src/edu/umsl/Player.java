package edu.umsl;

public class Player {

    private final ITakeTurnBehavior takeTurnBehavior;
    private final ColorType colorType;

    public Player(
        ITakeTurnBehavior takeTurnBehavior,
        ColorType colorType
    ) {
        this.takeTurnBehavior = takeTurnBehavior;
        this.colorType = colorType;
    }

    public ColorType getColorType() {
        return colorType;
    }

    public void executeTakeTurnBehavior() {
        takeTurnBehavior.takeTurn(colorType);
    }
}
