package Avaliacao;

import java.util.HashMap;

public class AvaliacaoComposite extends Avaliacao{
    private final HashMap<String,Avaliacao> avaliacoes = new HashMap<>();


    public AvaliacaoComposite(String nome, Disciplina d) {
        super(nome,d);
    }


    public void addAvaliacao(Avaliacao avaliacao){
        avaliacoes.put(avaliacao.getID(),avaliacao);
    }

    public float getNota(String ID){
        Avaliacao av = avaliacoes.get(ID);
        return av.getNota();
    }

    public float getMedia(){
        return (2*getNota("P1") + 2*getNota("P2") + getNota("T1"))/5;
    }

}
