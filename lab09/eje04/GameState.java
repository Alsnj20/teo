package lab09.eje04;

public class GameState {
    private static GameState instance;

    private int score;
    private int lives;
    private int level;
    private boolean gameOver;

    private GameState() {
        this.score = 0;
        this.lives = 3;
        this.level = 1;
        this.gameOver = false;
    }

    public static synchronized GameState getInstance() {
        if (instance == null) {
            instance = new GameState();
        }
        return instance;
    }

    public void addScore(int points) {
        this.score += points;
        if (this.score >= level * 100) {
            levelUp();
        }
    }

    public int getScore() {
        return score;
    }

    public void gameOver() {
        this.gameOver = true;
    }

    public void loseLife() {
        this.lives--;
        if (this.lives <= 0) {
            gameOver();
        }
    }

    public int getLives() {
        return lives;
    }

    public void levelUp() {
        this.level++;
    }

    public int getLevel() {
        return level;
    }

    public boolean isGameOver() {
        return gameOver;
    }

    public void reset() {
        this.score = 0;
        this.lives = 3;
        this.level = 1;
        this.gameOver = false;
    }

    @Override
    public String toString() {
        return String.format("Puntaje: %d | Vidas: %d | Nivel: %d", score, lives, level);
    }
}
