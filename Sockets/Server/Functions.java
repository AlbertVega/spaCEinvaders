package Server;

import java.lang.reflect.Method;
import java.util.Hashtable;
import Administrator.Players.Player1;
import Administrator.Players.Player2;
import Administrator.GUI.window;

public class Functions {
    private Hashtable<String, Method> Funciones = new Hashtable<String, Method>();
    private Player1 player1;
    private Player2 player2;
    private window window;

    public Functions(Player1 player1, Player2 player2, window window) {
        this.player1 = player1;
        this.player2 = player2;
        this.window = window;
        Method[] methods = this.getClass().getMethods();
        for (Method method : methods) {
            Funciones.put(method.getName(), method);
        }
    }

    public void updatePlayer1Life(Integer Life){
        player1.setLife(String.valueOf(Life));
        window.updatePlayers();
    }

    public void updatePlayer2Life(Integer Life){
        player2.setLife(String.valueOf(Life));
        window.updatePlayers();
    }

    public void updatePlayer1Score(Integer Score){
        player1.setScore(Score);
        window.updatePlayers();
    }

    public void updatePlayer2Score(Integer Score){
        player2.setScore(Score);
        window.updatePlayers();
    }

    public void execute (String function, Object... args) {
        try {
            Funciones.get(function).invoke(this, args);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }    
}
