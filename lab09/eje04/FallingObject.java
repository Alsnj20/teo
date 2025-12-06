package lab09.eje04;

import java.awt.*;
import java.util.Random;

public class FallingObject {
    private int x;
    private int y;
    private final int size = 40;
    private int speed;
    private boolean caught;
    private GameState gameState;
    private Color color;

    public FallingObject(int screenWidth) {
        Random rand = new Random();
        this.x = rand.nextInt(screenWidth - size);
        this.y = 0;
        this.gameState = GameState.getInstance();
        this.speed = 2 + (gameState.getLevel() / 2);
        this.caught = false;
        this.color = new Color(rand.nextInt(256), rand.nextInt(256), rand.nextInt(256));
    }

    public void update() {
        if (!caught) {
            y += speed;
        }
    }

    public void draw(Graphics g) {
        if (!caught) {
            g.setColor(color);
            g.fillOval(x, y, size, size);
        }
    }

    public boolean isOffScreen(int screenHeight) {
        return y > screenHeight;
    }

    public boolean checkCollision(Player player) {
        Rectangle objBounds = new Rectangle(x, y, size, size);
        if (objBounds.intersects(player.getBounds()) && !caught) {
            caught = true;
            gameState.addScore(10);
            return true;
        }
        return false;
    }

    public void missedByPlayer() {
        if (!caught) {
            gameState.loseLife();
        }
    }

    public boolean isCaught() {
        return caught;
    }
}
