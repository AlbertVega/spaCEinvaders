package Administrator.Players;

public class Player2 {
    private String Life;
    private Integer Score, PORT;

    public String getLife() {
        return this.Life;
    }

    public void setLife(String life) {
        this.Life = life;
    }

    public void setScore(Integer score) {
        this.Score = score;
    }

    public void setPORT(Integer pORT) {
        this.PORT = pORT;
    }

    public Integer getScore() {
        return this.Score;
    }

    public Integer getPORT() {
        return this.PORT;
    }

    public Player2(String Life, Integer Score) {
        this.Life = Life;
        this.Score = Score;
    }
    
}
