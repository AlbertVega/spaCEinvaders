package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import Administrator.Players.Player1;
import Administrator.Players.Player2;


public class Server {
    private PrintWriter salida;
    private Socket cliente;
    private Integer PUERTO;
    private Gson gson;
    private BufferedReader entrada;
    private ServerSocket servidor;
    private String mensaje;

    public void Response(String respuesta) throws IOException {
        salida.println(respuesta);
        System.out.println("Respuesta enviada: " + respuesta);
    }

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
    
    public Server(Player1 player1, Player2 player2) throws IOException{
        this.PUERTO = 8080;
        this.servidor = new ServerSocket(this.PUERTO);
        System.out.println("Servidor iniciado en el puerto " + this.PUERTO);
        this.gson = new Gson();
        //player1.setPORT(1234);        
    }

    private void listener() throws IOException{
        while (true) {
            mensaje = reader(entrada); 
            System.out.println("Mensaje recibido: " + mensaje);
            // Convertir el mensaje recibido en un objeto JSON
            //ACA VUELVE A HACER UN .JSON El STRING QUE LLEGO
            JsonElement jsonElement = gson.fromJson(mensaje, JsonElement.class);
            String respuesta = jsonElement.getAsJsonObject().get("mensaje").getAsString();
            //System.out.println("Mensaje recibido 1: " + jsonElement.toString());
            System.out.println(respuesta);            
            if (respuesta.equals("respondame")) {
                System.out.println("\nta bien\n");
                Response("Hola uwu");
            }
        }
    }

    public void StartServer() throws IOException{    
        Thread thread = new Thread(new Runnable() {
            public void run() {
                try {
                    while (true) {
                        cliente = servidor.accept();
                        salida = new PrintWriter(cliente.getOutputStream(), true);            
                        entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
                        System.out.println("Conexión establecida con el cliente " + cliente.getInetAddress());
            
                        System.out.println("\n\n\nNUEVO CLIENTE EN PUERTO: " + cliente.getPort() + "\n\n\n");
                        
                        Thread t = new Thread(new Runnable() { //hilo que se encarga de escuchar al cliente
                            public void run() {
                                try {
                                    listener();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        });
                        t.start();
                    }
                }catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        thread.start();  
    }

    /*public static void main(String[] args) throws IOException {

        //int puerto = 8080;
        //servidor = new ServerSocket(puerto);        
        //Gson gson = new Gson();

        while (true) {
            this.cliente = this.servidor.accept();
            System.out.println("Conexión establecida con el cliente " + cliente.getInetAddress());

            System.out.println("\n\n\nNUEVO CLIENTE EN PUERTO: " + cliente.getPort() + "\n\n\n");
            
            Thread t = new Thread(new Runnable() { //hilo que se encarga de escuchar al cliente
                public void run() {
                    try {
                        BufferedReader entrada;
                        try {
                            while (true) {
                                entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
                                String mensaje = reader(entrada); 
                                System.out.println("Mensaje recibido: " + mensaje);
                                // Convertir el mensaje recibido en un objeto JSON
                                //ACA VUELVE A HACER UN .JSON El STRING QUE LLEGO
                                JsonElement jsonElement = gson.fromJson(mensaje, JsonElement.class);
                                String respuesta = jsonElement.getAsJsonObject().get("mensaje").getAsString();
                                //System.out.println("Mensaje recibido 1: " + jsonElement.toString());

                                System.out.println(respuesta);
                                
                                if (respuesta.equals("respondame")) {
                                    System.out.println("\nta bien\n");
                                    Response(cliente);
                                }
                            }
                        } catch (IOException e) {
                            e.printStackTrace();
                        }  
                              
                        
                    } finally {
                        try {
                            cliente.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            });
            t.start();
        }
    }*/
}
