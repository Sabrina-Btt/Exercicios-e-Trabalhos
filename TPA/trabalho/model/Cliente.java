package model;

import model.Delivery;


public class Cliente extends Pessoa{
	private Delivery delivery;
	private String endereco;
	private int telefone;

	public String getEndereco(){
		return this.endereco;
	}

	public void setEndereco(String endereco){
		this.endereco = endereco;
	}

	public int getTelefone(){
		return this.telefone;
	}

	public void setTelefone(int telefone){
		this.telefone = telefone;
	}

	public Delivery getDelivery(){
		return this.delivery;
	}

	public void setDelivery(Delivery delivery){
		this.delivery = delivery;
	}

	
	public Cliente(String nome, int cpf, String endereco, int telefone) {
        super(nome, cpf);
        setEndereco(endereco);
        setTelefone(telefone);
    }
}