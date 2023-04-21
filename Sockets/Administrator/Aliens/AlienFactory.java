package Administrator.Aliens;

/**
 * Clase que crea aliens mediante el patron de diseño Factory
 */
public class AlienFactory {

    /**
     * Este metdo crea un alien segun el tipo que se le pase por parametro
     * @param type tipo de alien que se quiere crear
     * @param name nombre del alien que se quiere crear
     * @return el alien creado
     */
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
