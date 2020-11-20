
package Avaliacao;


public class Trabalho extends Avaliacao{
    private String descricao;
    
    public Trabalho(String ID,Disciplina disciplina){
        super(ID,disciplina);
    }
    
    public void setDescricao(String descricao){
        this.descricao = descricao;
    }

    public String getDescricao(){
        return descricao;
    }
}
