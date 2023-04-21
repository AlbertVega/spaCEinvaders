package Administrator.Aliens;

/**
 * Clase que se encarga de crear los aliens tipo Calamar.
 */
public class Calamar implements Alien{
    private Integer XPos;
    private Integer YPos;
    private String name;
    
    /**
     * Constructor de la clase Calamar.
     * @param name tipo de alien.
     */
    public Calamar(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return this.name;
    }

    @Override
    public Integer getXPos() {
        return this.XPos;
    }

    @Override
    public Integer getYPos() {
        return this.YPos;
    }

    @Override
    public void setXPos(Integer XPos) {
        this.XPos = XPos;
    }

    @Override
    public void setYPos(Integer YPos) {
        this.YPos = YPos;
    }
    
}
