package Administrator.Aliens;
/**
 * Clase que se encarga de crear los aliens tipo Pulpo.
 */
public class Pulpo implements Alien {
    private Integer XPos;
    private Integer YPos;
    private String name;

    /**
     * Constructor de la clase Pulpo.
     * @param name tipo de alien.
     */
    public Pulpo(String name) {
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
