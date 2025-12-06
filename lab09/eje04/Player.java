package lab09.eje04;

import java.awt.*;

public class Player {
    private int x;
    private int y;
    private final int width = 60;
    private final int height = 60;
    private final int speed = 15;
    private GameState gameState;

    public Player(int startX, int startY) {
        this.x = startX;
        this.y = startY;
        this.gameState = GameState.getInstance();
    }

    public void moveLeft() {
        if (x > 0) {
            x -= speed;
        } else {
            gameState.gameOver();
        }
    }

    public void moveRight(int screenWidth) {
        if (x + width < screenWidth) {
            x += speed;
        } else {
            gameState.gameOver();
        }
    }

    public void draw(Graphics g) {
        g.setColor(Color.BLUE);
        g.fillRect(x, y, width, height);
    }

    public Rectangle getBounds() {
        return new Rectangle(x, y, width, height);
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
