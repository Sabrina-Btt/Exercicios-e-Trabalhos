package model;


abstract class Pessoa{
	private String nome;
	private int cpf;

	public String getNome(){
		return this.nome;
	}

	public void setNome(String nome){
		this.nome = nome;
	}

	public int getCpf(){
		return this.cpf;
	}

	public void setCpf(int cpf){
		this.cpf = cpf;
	}

	public Pessoa(String nome, int cpf){
		setNome(nome);
		setCpf(cpf); 
	}
}