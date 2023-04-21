package Server;

import com.google.gson.JsonObject;

/**
 * Clase que crea los JSON para enviar al cliente
 */
public class JSONBuilder {

    /**
     * Crea un JSON con el mensaje de que se creo un alien
     * @param alien Tipo de alien
     * @param posX Posicion en X
     * @param posY  Posicion en Y
     * @return JSON con el mensaje de que se creo un alien
     */
    public String createAlien(String alien, Integer posX, Integer posY) {
        JsonObject json = new JsonObject();  // Crear un objeto JSON para la respuesta
        json.addProperty("message", "AlienCreated");
        json.addProperty("alien", alien);
        json.addProperty("PosX", posX);
        json.addProperty("PosY", posY);
        return json.toString();
    }
    
    /**
     * Crea un JSON con el mensaje de que se cambio la velocidad
     * @param speed Velocidad de los aliens
     * @return JSON con el mensaje de que se cambio la velocidad
     */
    public String setSpeed(String speed) {
        JsonObject json = new JsonObject(); 
        json.addProperty("message", "SpeedSet");
        json.addProperty("speed", speed);
        return json.toString();
    }

    /**
     * Crea un JSON con el mensaje de que se cambio la posicion de un alien
     * @param alien Tipo de alien
     * @param posX Posicion en X
     * @param posY Posicion en Y
     * @return JSON con el mensaje de que se cambio la posicion de un alien
     */
    public String setPositions(String alien, Integer posX, Integer posY){
        JsonObject json = new JsonObject(); 
        json.addProperty("message", "PositionsSet");
        json.addProperty("alien", alien);
        json.addProperty("PosX", posX);
        json.addProperty("PosY", posY);
        return json.toString();
    }
}
