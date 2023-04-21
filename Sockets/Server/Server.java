package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;

import com.google.gson.Gson;
import com.google.gson.JsonElement;
import Administrator.Players.Player1;
import Administrator.Players.Player2;

/**
 * Clase que se encarga del manejo del servidor.
 */
public class Server {
    private Integer PUERTO;
    private Gson gson;
    private ServerSocket servidor;
    private Player1 Player1;
    private Player2 Player2;
    private Boolean FLAG = false;
    private Functions Functions;

    /**
     * Este metodo se encarga de enviar mensajes al cliente 1.
     * @param respuesta mensaje que se le envia al cliente.
     * @throws IOException excepcion en caso de que no se pueda enviar el mensaje.
     */
    public void response1(String respuesta) throws IOException {
        Player1.salida.println(respuesta);
        System.out.println("Respuesta enviada: " + respuesta);
    }

    /**
     * Este metodo se encarga de enviar mensajes al cliente 2.
     * @param respuesta mensaje que se le envia al cliente.
     * @throws IOException excepcion en caso de que no se pueda enviar el mensaje.
     */
    public void response2(String respuesta) throws IOException {
        Player2.salida.println(respuesta);
        System.out.println("Respuesta enviada: " + respuesta);
    }

    /**
     * Este metodo se encarga de leer los mensajes que envian los clientes.
     * @param reader instancia del objeto BufferedReader que se encarga de leer los mensajes.
     * @return mensaje que envia el cliente.
     * @throws IOException excepcion en caso de que no se pueda leer el mensaje.
     */
    public static String reader(BufferedReader reader) throws IOException {
        String line = reader.readLine();
        StringBuilder builder = new StringBuilder();
        while (line != null) {
            if (line.contains("}")) {
                builder.append(line);
                System.out.println("Fin de la lectura");
                break;
             }
            builder.append(line);
            line = reader.readLine();
           
        }
        return builder.toString();
    }
    
    /**
     * Constructor de la clase.
     * @param player1 instancia del objeto player1.
     * @param player2 instancia del objeto player2.
     * @throws IOException excepcion en caso de que no se pueda iniciar el servidor.
     */
    public Server(Player1 player1, Player2 player2) throws IOException{
        this.PUERTO = 8080;
        this.servidor = new ServerSocket(this.PUERTO);
        System.out.println("Servidor iniciado en el puerto " + this.PUERTO);
        this.gson = new Gson();
        this.Player1 = player1;
        this.Player2 = player2;
    }

    /**
     * Este metodo se encarga de escuchar los mensajes que envian los clientes.
     * @param entrada instancia del objeto BufferedReader que se encarga de leer los mensajes.
     * @throws IOException excepcion en caso de que no se pueda leer el mensaje.
     */
    private void listener(BufferedReader entrada) throws IOException{
        while (true) {
            String mensaje = reader(entrada); 
            System.out.println("Mensaje recibido: " + mensaje);
            // Convertir el mensaje recibido en un objeto JSON
            //ACA VUELVE A HACER UN .JSON El STRING QUE LLEGO
            JsonElement jsonElement = gson.fromJson(mensaje, JsonElement.class);
            String respuesta = jsonElement.getAsJsonObject().get("mensaje").getAsString();
            if (respuesta.equals("P1Life")){
                Functions.execute("updatePlayer1Life",  Integer.valueOf(jsonElement.getAsJsonObject().get("updatePlayer1Life").getAsString()));             
                System.out.println("Vida de P1 actualizada");

            }else if (respuesta.equals("P2Life")){
                Functions.execute("updatePlayer2Life",  Integer.valueOf(jsonElement.getAsJsonObject().get("updatePlayer2Life").getAsString()));             
                System.out.println("Vida de P2 actualizada");

            }else if (respuesta.equals("P1Score")){
                Functions.execute("updatePlayer1Score",  Integer.valueOf(jsonElement.getAsJsonObject().get("updatePlayer1Score").getAsString()));             
                System.out.println("Puntaje de P1 actualizado");

            }else if (respuesta.equals("P2Score")){
                Functions.execute("updatePlayer2Score",  Integer.valueOf(jsonElement.getAsJsonObject().get("updatePlayer2Score").getAsString()));             
                System.out.println("Puntaje de P2 actualizado");
            }
            //System.out.println("Mensaje recibido 1: " + jsonElement.toString());
            System.out.println(respuesta);         
        }
    }

    /**
     * Este metodo se encarga de iniciar el servidor y mantenerlo activo
     * @throws IOException excepcion en caso de que no se pueda iniciar el servidor
     */
    public void StartServer() throws IOException{    
        Thread thread = new Thread(new Runnable() {
            public void run() {
                try {
                    while (true) {
                        if (!FLAG){
                            Player1.socket = servidor.accept();
                            Player1.salida = new PrintWriter(Player1.socket.getOutputStream(), true);
                            Player1.entrada = new BufferedReader(new InputStreamReader(Player1.socket.getInputStream()));
                            Player1.setPORT(Player1.socket.getPort());
                            System.out.println("Conexión establecida con el cliente " + Player1.socket.getInetAddress());
                            FLAG = true;
                            Thread t = new Thread(new Runnable() { //hilo que se encarga de escuchar al cliente
                                public void run() {
                                    try {
                                        listener(Player1.entrada);
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                }
                            });
                            t.start();
                        }else {
                            Player2.socket = servidor.accept();
                            Player2.salida = new PrintWriter(Player2.socket.getOutputStream(), true);
                            Player2.entrada = new BufferedReader(new InputStreamReader(Player2.socket.getInputStream()));
                            Player2.setPORT(Player2.socket.getPort());
                            System.out.println("Conexión establecida con el cliente " + Player2.socket.getInetAddress());
                            FLAG = false;
                            Thread t = new Thread(new Runnable() { //hilo que se encarga de escuchar al cliente
                                public void run() {
                                    try {
                                        listener(Player2.entrada);
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                }
                            });
                            t.start();
                        }                        
                    }
                }catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        thread.start();  
    }

    public void setFunctions(Functions functions){
        this.Functions = functions;
    }
}
