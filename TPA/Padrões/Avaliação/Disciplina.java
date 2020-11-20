package Avaliacao;

import java.util.ArrayList;

public class Disciplina {
    private String nome;
    private ArrayList<Aluno> inscritos;
    
    public Disciplina(String nome){
        this.nome = nome;
    }
    
    public String getNome(){
        return nome;
    }
}
