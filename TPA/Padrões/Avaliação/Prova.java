package Avaliacao;

import java.util.ArrayList;

public class Prova extends Avaliacao{
    private final ArrayList<String> questoes;
    
    public Prova(String ID,Disciplina disciplina){
        super(ID,disciplina);
        questoes = new ArrayList<String>();
    }
    
    public void addQuestao(String questao){
        questoes.add(questao);
    }
    
    public String getProva(){
        String prova = "Prova\n";
        for(String s: questoes)
            prova += s + "\n";
        return prova;
    }
}
