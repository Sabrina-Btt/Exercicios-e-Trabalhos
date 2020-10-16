package model;

public class Pedido{
	private int numero;
	private boolean statusPronto;
	private String descriçao;

	public int getNumero(){
		return this.numero;
	}

	public void setNumero(int numero){
		this.numero= numero;
	}
    
    public boolean getStatusPronto(){
    	return this.statusPronto;
    }

    public void setStatusPronto(boolean statusPronto){
    	this.statusPronto=statusPronto;
    }

    public String getDescricao(){
    	return this.descriçao;
    }

    public void setDescricao(String descriçao){
    	this.descriçao = descriçao;
    }

    public Pedido(int numero, String descriçao){
        setStatusPronto(false);
    	setNumero(numero);
    	setDescricao(descriçao);
    }

}