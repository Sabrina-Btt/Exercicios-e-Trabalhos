package Avaliacao;

public class AvaliacaoFacade {
    public AvaliacaoComposite avaliacaoPadrao(Disciplina d1){
        AvaliacaoComposite av1 = new AvaliacaoComposite(d1.getNome(),d1);
        av1.addAvaliacao(new Prova("P1",d1));
        av1.addAvaliacao(new Prova("P2",d1));
        av1.addAvaliacao(new Trabalho("T1",d1));
        return av1;
    }
}
