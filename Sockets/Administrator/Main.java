package Administrator;

import java.io.IOException;

import Administrator.Players.Player1;
import Administrator.Players.Player2;
import Server.Server;

public class Main {

    public static void main(String[] args) throws IOException {
        Player1 player1 = new Player1("3", 0);
        Player2 player2 = new Player2("3", 0);
        window window = new window(player1, player2);
        Server server = new Server(player1, player2);
        server.StartServer();
    }
    
}
