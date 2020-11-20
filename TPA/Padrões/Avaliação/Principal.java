package Avaliacao;

public class Principal {
    public static void main(String[] args){
        Disciplina d1 = new Disciplina("TPA");
        Disciplina d2 = new Disciplina("CG");
        
        Aluno a1 = new Aluno("João");
        Aluno a2 = new Aluno("José");
        Aluno a3 = new Aluno("Maria");

        AvaliacaoFacade av = new AvaliacaoFacade();
        a1.addAvaliacao(av.avaliacaoPadrao(d1));
        a2.addAvaliacao(av.avaliacaoPadrao(d2));

        float media1 = a1.getMedia(d1);
        float media2 = a2.getMedia(d2);

        System.out.println(media1);
        System.out.println(media2);

    }
}
