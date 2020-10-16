package control;

import model.Delivery;
import model.Pedido;
import model.Cliente;
import java.util.ArrayList;


public class ControlPedidos{
	ControlClientes crtC = new ControlClientes();
	ArrayList<Pedido> pedidos = new ArrayList<>();
	ArrayList<Delivery> pedidosD = new ArrayList<>();

	public boolean realizaPedido(int numero, String descricao){
		Pedido p = new Pedido(numero, descricao);
		pedidos.add(p);
		return true;

	}

	public boolean realizaPedidoDelivery(int numero, String descricao, float valorEntrega, int cpf){
		Delivery d = new Delivery(numero, descricao, valorEntrega);
		pedidosD.add(d);
		Cliente c = crtC.buscaCliente(cpf);
		if(c==null)
			return false;
		else
			c.setDelivery(d);
		return true;

		
	}



}