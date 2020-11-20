package Avaliacao;

public abstract class Avaliacao {
    private final String ID;
    private float nota;
    private final Disciplina disciplina;
    
    public Avaliacao(String ID,Disciplina disciplina){
        nota = 0;
        this.disciplina = disciplina;
        this.ID = ID;
    }

    
    public float getNota(){
        return nota;
    }
    
    public void setNota(float nota){
        this.nota = nota;
    }
    
    public String getID(){
        return ID;
    }

    public Disciplina getDisciplina() {
        return disciplina;
    }
}
