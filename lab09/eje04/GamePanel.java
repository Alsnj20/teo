package lab09.eje04;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Iterator;

public class GamePanel extends JPanel implements ActionListener, KeyListener {
    private final int WIDTH = 600;
    private final int HEIGHT = 400;
    private Timer timer;
    private Player player;
    private ArrayList<FallingObject> fallingObjects;
    private GameState gameState;
    private int spawnCounter;

    public GamePanel() {
        setPreferredSize(new Dimension(WIDTH, HEIGHT));
        setBackground(Color.BLACK);
        setFocusable(true);
        addKeyListener(this);

        gameState = GameState.getInstance();
        gameState.reset();

        player = new Player(WIDTH / 2 - 25, HEIGHT - 60);
        fallingObjects = new ArrayList<>();
        spawnCounter = 0;

        timer = new Timer(20, this);
        timer.start();
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (!gameState.isGameOver()) {
            spawnCounter++;
            int spawnRate = Math.max(60 - gameState.getLevel() * 3, 30);
            if (spawnCounter >= spawnRate) {
                fallingObjects.add(new FallingObject(WIDTH));
                spawnCounter = 0;
            }

            Iterator<FallingObject> iterator = fallingObjects.iterator();
            while (iterator.hasNext()) {
                FallingObject obj = iterator.next();
                obj.update();
                obj.checkCollision(player);

                if (obj.isOffScreen(HEIGHT)) {
                    if (!obj.isCaught()) {
                        obj.missedByPlayer();
                    }
                    iterator.remove();
                }
            }
        }

        repaint();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        player.draw(g);

        for (FallingObject obj : fallingObjects) {
            obj.draw(g);
        }

        g.setColor(Color.WHITE);
        g.setFont(new Font("Arial", Font.BOLD, 16));
        g.drawString(gameState.toString(), 10, 20);

        if (gameState.isGameOver()) {
            g.setColor(Color.RED);
            g.setFont(new Font("Arial", Font.BOLD, 30));
            g.drawString("GAME OVER", WIDTH / 2 - 100, HEIGHT / 2);
            g.setFont(new Font("Arial", Font.PLAIN, 16));
            g.drawString("R para reiniciar", WIDTH / 2 - 70, HEIGHT / 2 + 30);
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (!gameState.isGameOver()) {
            if (e.getKeyCode() == KeyEvent.VK_LEFT || e.getKeyCode() == KeyEvent.VK_A) {
                player.moveLeft();
            }
            if (e.getKeyCode() == KeyEvent.VK_RIGHT || e.getKeyCode() == KeyEvent.VK_D) {
                player.moveRight(WIDTH);
            }
        }

        if (e.getKeyCode() == KeyEvent.VK_R && gameState.isGameOver()) {
            gameState.reset();
            fallingObjects.clear();
            player = new Player(WIDTH / 2 - 25, HEIGHT - 60);
            spawnCounter = 0;
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
    }

    @Override
    public void keyTyped(KeyEvent e) {
    }
}
