package control;

import java.util.ArrayList;
import model.Cliente;

public class ControlClientes{
    ArrayList<Cliente> clientes = new ArrayList<>();


    public boolean cadastrar(String nome, int cpf, int telefone, String endereco){
        if (clientes.size()==0){
            Cliente c = new Cliente(nome, cpf, endereco, telefone);
            clientes.add(c);
            return true;}

        for (Cliente cl : clientes) {
            if (cl.getCpf() == cpf)
                return false;
            else {
                Cliente c = new Cliente(nome, cpf, endereco, telefone);
                clientes.add(c);
                return true;
            }
        }
        return true;
    }

    public Cliente buscaCliente(int cpf){
        for(Cliente c : clientes){
            if(c.getCpf()==cpf){
                return c;
            }
            else
                return null;
        }
        return null;
    }

}