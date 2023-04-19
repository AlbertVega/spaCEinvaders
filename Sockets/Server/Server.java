package Server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

public class Server {

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
    
    public static void main(String[] args) throws IOException {
        int puerto = 8080;
        ServerSocket servidor = new ServerSocket(puerto);
        System.out.println("Servidor iniciado en el puerto " + puerto);
        Gson gson = new Gson();

        while (true) {
            Socket cliente = servidor.accept();
            System.out.println("Conexión establecida con el cliente " + cliente.getInetAddress());

            System.out.println("\n\n\nNUEVO CLIENTE EN PUERTO: " + cliente.getPort() + "\n\n\n");
            
            Thread t = new Thread(new Runnable() {
                public void run() {
                    try {
                        BufferedReader entrada = new BufferedReader(new InputStreamReader(cliente.getInputStream()));
                        PrintWriter salida = new PrintWriter(cliente.getOutputStream(), true);
                        Scanner scanner = new Scanner(System.in);
                        while (true) {
                            String mensaje = reader(entrada); 
                            System.out.println("Mensaje recibido: " + mensaje);
                            // Convertir el mensaje recibido en un objeto JSON
                            //ACA VUELVE A HACER UN .JSON El STRING QUE LLEGO
                            JsonElement jsonElement = gson.fromJson(mensaje, JsonElement.class);
                            System.out.println("Mensaje recibido 1: " + jsonElement.toString());

                            
                            // Crear un objeto JSON para la respuesta
                            JsonObject respuestaJson = new JsonObject();
                            String respuesta = scanner.nextLine();
                            //ACA ENVIA UN NUEVO .Json y se crea un los elementos 
                            respuestaJson.addProperty("respuesta", respuesta);
                            respuestaJson.addProperty("nombre", servidor.getInetAddress().getHostName());
                            String respuestaJsonString = respuestaJson.toString();

                            System.out.println("Respuesta enviada: " + respuestaJsonString);

                            // Enviar la respuesta al cliente en formato JSON
                            salida.println(respuestaJsonString);

                        }
                    } catch (IOException e) {
                        e.printStackTrace();
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
    }
}
