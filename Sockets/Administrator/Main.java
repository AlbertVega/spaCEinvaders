package Administrator;

import java.io.IOException;

import Administrator.Aliens.AlienFactory;
import Administrator.GUI.window;
import Administrator.Players.Player1;
import Administrator.Players.Player2;
import Server.Functions;
import Server.Server;

public class Main {

    public static void main(String[] args) throws IOException {
        Player1 player1 = new Player1("3", 0);
        Player2 player2 = new Player2("3", 0);
        AlienFactory alienFactory = new AlienFactory();
        Server server = new Server(player1, player2);
        server.StartServer();
        window window = new window(player1, player2, alienFactory, server);
        Functions functions = new Functions(player1, player2, window);
        server.setFunctions(functions);
    }
    
}
