package Administrator.Aliens;

/**
 * Clase que se encarga de crear los aliens tipo Cangrejo.
 */
public class Cangrejo implements Alien{
    private Integer XPos;
    private Integer YPos;
    private String name;

    /**
     * Constructor de la clase Cangrejo.
     * @param name tipo de alien.
    */
    public Cangrejo(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return this.name;
    }
        
    @Override
    public void setXPos(Integer XPos) {
        this.XPos = XPos;
    }
    
    @Override
    public void setYPos(Integer YPos) {
        this.YPos = YPos;
    }
    
    @Override
    public Integer getXPos() {
        return this.XPos;
    }
    
    @Override
    public Integer getYPos() {
        return this.YPos;
    }
    
}
