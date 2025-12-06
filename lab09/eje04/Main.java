package lab09.eje04;

import javax.swing.*;

public class Main {
    public static void main(String[] args) {
        GameState gameState = GameState.getInstance();
        System.out.println("Estado inicial: " + gameState);

        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("juego ese");
            GamePanel gamePanel = new GamePanel();

            frame.add(gamePanel);
            frame.pack();
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLocationRelativeTo(null);
            frame.setResizable(false);
            frame.setVisible(true);
        });
    }
}
