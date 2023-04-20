import java.util.ArrayList;
import java.util.List;


public interface Observador{
    void update();
}

class espectador implements Observador {
    private List<Observador> Observadors = new ArrayList<>();
    private int state;

    public int getState() {
        return state;
    }

    public void setState(int state) {
        this.state = state;
        notifyAllObservadors();
    }

    public void attach(Observador Observador){
        Observadors.add(Observador);		
    }

    public void notifyAllObservadors(){
        for (Observador Observador : Observadors) {
            Observador.update();
        }
    }	

    @Override
    public void update() {
        System.out.println( "State: " + state ); 
    }	
}

    

