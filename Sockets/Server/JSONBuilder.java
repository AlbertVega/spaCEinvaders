package Server;

import com.google.gson.JsonObject;

public class JSONBuilder {

    public String createAlien(String alien, Integer posX, Integer posY) {
        JsonObject json = new JsonObject();  // Crear un objeto JSON para la respuesta
        json.addProperty("message", "AlienCreated");
        json.addProperty("alien", alien);
        json.addProperty("PosX", posX);
        json.addProperty("PosY", posY);
        return json.toString();
    }    
}
