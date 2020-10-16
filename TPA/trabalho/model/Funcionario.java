package model;

public class Funcionario extends Pessoa {
        private final int id;
        private float comissao; /*não sei ainda*/

        public void calculaComissao(){};

        public int getId(){
            return this.id;
        }

        public Funcionario(String nome, int cpf, int id){
            super(nome,cpf);
            this.id = id;
        }

}
