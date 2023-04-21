package Administrator.Aliens;

/**
 * Interfaz implementada por los aliens para que puedan ser creados por la clase AlienFactory.
 */
public interface Alien {
    /**
     * Este metodo se encarga de asignar la posicion en X del alien.
     * @param XPos posicion en X del alien.
    */
    public void setXPos(Integer XPos);
    /**
     * Este metodo se encarga de asignar la posicion en Y del alien.
     * @param YPos posicion en Y del alien.
    */
    public void setYPos(Integer YPos);
    /**
     * Este metodo se encarga de retornar la posicion en X del alien.
     * @return posicion en X del alien.
    */
    public Integer getXPos();
    /**
     * Este metodo se encarga de retornar la posicion en Y del alien.
     * @return posicion en Y del alien.
    */
    public Integer getYPos();
    /**
     * Este metodo se encarga de retornar el nombre del alien.
     * @return nombre del alien.
    */
    public String getName();
}
