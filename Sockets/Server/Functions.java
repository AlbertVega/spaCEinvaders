package Server;

import java.lang.reflect.Method;
import java.util.Hashtable;
import Administrator.Players.Player1;
import Administrator.Players.Player2;
import Administrator.GUI.window;

/**
 * Clase que contiene las funciones que se pueden ejecutar desde el servidor
 */
public class Functions {
    private Hashtable<String, Method> Funciones = new Hashtable<String, Method>();
    private Player1 player1;
    private Player2 player2;
    private window window;

    /**
     * Constructor de la clase Functions
     * @param player1 Jugador 1
     * @param player2 Jugador 2
     * @param window Ventana
     */
    public Functions(Player1 player1, Player2 player2, window window) {
        this.player1 = player1;
        this.player2 = player2;
        this.window = window;
        Method[] methods = this.getClass().getMethods();
        for (Method method : methods) {
            Funciones.put(method.getName(), method);
        }
    }

    /**
     * Función que actualiza la vida de los jugadores.
     * @param Life Vida.
     */
    public void updatePlayer1Life(Integer Life){
        player1.setLife(String.valueOf(Life));
        window.updatePlayers();
    }

    /**
     * Función que actualiza la vida de los jugadores.
     * @param Life Vida.
     */
    public void updatePlayer2Life(Integer Life){
        player2.setLife(String.valueOf(Life));
        window.updatePlayers();
    }

    /**
     * Función que actualiza el puntaje del jugador 1.
     * @param Score Puntaje.
     */
    public void updatePlayer1Score(Integer Score){
        player1.setScore(Score);
        window.updatePlayers();
    }

    /**
     * Función que actualiza el puntaje del jugador 2.
     * @param Score Puntaje.
     */
    public void updatePlayer2Score(Integer Score){
        player2.setScore(Score);
        window.updatePlayers();
    }

    /**
     * Funcion que ejecuta las peticiones del cliente.
     * @param function Función a ejecutar.
     * @param args Argumentos de la función.
     */
    public void execute (String function, Object... args) {
        try {
            Funciones.get(function).invoke(this, args);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }    
}
