package model;

public class Delivery extends Pedido{
	private boolean statusEntrega;
	private float valorEntrega;

	public boolean getStatusEntrega(){
		return this.statusEntrega;
	} 

	public void setStatusEntrega(boolean statusEntrega){
		this.statusEntrega = statusEntrega;
	}

	public float getValorEntrega(){
		return this.valorEntrega;
	}

	public void setValorEntrega(float valorEntrega){
		this.valorEntrega = valorEntrega;
	}


	public Delivery(int numero, String descricao, float valorEntrega){
		super(numero, descricao);
		setStatusEntrega(false);
		setValorEntrega(valorEntrega);
	}


}