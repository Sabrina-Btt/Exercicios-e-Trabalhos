package Avaliacao;

import java.util.ArrayList;

public class Aluno {
    private String nome;
    private final ArrayList<Avaliacao> avaliacoes;


    public Aluno(String nome){
        this.nome = nome;
        avaliacoes = new ArrayList<>();
    }
    
    public void addAvaliacao(AvaliacaoComposite avaliacao){
        avaliacoes.add(avaliacao);
    }


    public float getMedia(Disciplina d){
        float media = 0;
        int c = 0;
        for(Avaliacao av: avaliacoes){
            if(av.getDisciplina().getNome().equals(d.getNome())){
                if(av.getID().equals(d.getNome())){
                    AvaliacaoComposite av1 = (AvaliacaoComposite) av;
                    media += av1.getMedia();
                }else{
                    media += av.getNota();
                }
                c++;
            }
        }
        return media/c;
    }


}
