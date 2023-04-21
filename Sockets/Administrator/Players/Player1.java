package Administrator.Players;

import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Clase que se encarga de manejar los datos del jugador 1.
 */
public class Player1 {
    private String Life;
    private Integer Score, PORT;
    public Socket socket;
    public PrintWriter salida;
    public BufferedReader entrada;

    /**
     * Este metodo se encarga de retornar la vida del jugador 1.
     * @return vida del jugador 1.
     */
    public String getLife() {
        return this.Life;
    }

    /**
     * Este metodo se encarga de asignar la vida del jugador 1.
     * @param life vida del jugador 1.
     */
    public void setLife(String life) {
        this.Life = life;
    }
    
    /**
     * Este metodo se encarga de asignar el puntaje del jugador 1.
     * @param score puntaje del jugador 1.
     */
    public void setScore(Integer score) {
        this.Score = score;
    }
    
    /**
     * Este metodo se encarga de asignar el puerto del jugador 1.
     * @param pORT puerto del jugador 1.
     */
    public void setPORT(Integer pORT) {
        this.PORT = pORT;
    }

    /**
     * Este metodo se encarga de retornar el puntaje del jugador 1.
     * @return puntaje del jugador 1.
     */
    public Integer getScore() {
        return this.Score;
    }

    /**
     * Este metodo se encarga de retornar el puerto del jugador 1.
     * @return puerto del jugador 1.
     */
    public Integer getPORT() {
        return this.PORT;
    }
    
    /**
     * Constructor de la clase Player1.
     * @param Life vida del jugador 1.
     * @param Score puntaje del jugador 1.
     */
    public Player1(String Life, Integer Score) {
        this.Life = Life;
        this.Score = Score;
    }
}
