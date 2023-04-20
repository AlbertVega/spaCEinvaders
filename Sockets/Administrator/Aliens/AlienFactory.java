package Administrator.Aliens;

public class AlienFactory {

    public Alien createAlien(String type, String name) {
        if (type.equals("Calamar")) {
            return new Calamar(name);

        } else if (type.equals("Pulpo")) {
            return new Pulpo(name);

        } else if (type.equals("Cangrejo")) {
            return new Cangrejo(name);
            
        } else {
            return null;
        }
    }
    
}
