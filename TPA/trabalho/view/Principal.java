package view;

import java.util.Scanner;
import control.ControlClientes;
import control.ControlPedidos;


public class Principal{
  ControlClientes crtC = new ControlClientes();
  ControlPedidos crtP = new ControlPedidos();
	public static void main(String[] args) {
        Principal p = new Principal();
        int opcao;

        do {
            System.out.println("Sistema de controle de pedidos");
            System.out.println("1- Cadastrar cliente");
            System.out.println("2- Realizar novo pedido");
            System.out.println("3- Realizar novo pedido delivery");
            System.out.println("4- Sair");
            Scanner scanner = new Scanner(System.in);
            opcao = scanner.nextInt();
            switch (opcao) {
                case 1:
                    p.cadastrarCliente();
                    break;
                case 2:
                    p.realizarPedido();
                    break;
                case 3:
                    p.realizarPedidoDelivery();
                    break;

            }
        }while(opcao!= 4);
    }

  private void cadastrarCliente(){
        Scanner scanner = new Scanner(System.in);
        System.out.println("Cadastro de cliente");
        System.out.print("Digite o nome do cliente: ");
        String nome = scanner.next();
        
        int cpf;
        System.out.println("CPF: "); 
        cpf = scanner.nextInt();

        int telefone;
        System.out.println("Telefone para contato: ");
        telefone = scanner.nextInt();


        System.out.println("Endereco: ");
        String endereco = scanner.next();

        if(crtC.cadastrar(nome, cpf, telefone, endereco))
            System.out.println("Cliente cadastrado com sucesso! ");
        else
            System.out.println("Cliente já cadastrado, checar cpf ");
    }

    private void realizarPedido(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite a descrição do pedido: ");
        String descricao = scanner.next();

        int numero;
        System.out.println("Entre com o numero do pedido: ");
        numero = scanner.nextInt();

        if(crtP.realizaPedido(numero, descricao))
            System.out.println("Pedido realizado com sucesso!");

    }

    private void realizarPedidoDelivery(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite a descrição do pedido: ");
        String descricao = scanner.next();

        int numero;
        System.out.println("Entre com o numero do pedido: ");
        numero = scanner.nextInt();

        float valorEntrega;
        System.out.println("Entre com a taxa de entrega: ");
        valorEntrega = scanner.nextFloat();

        int cpf;
        System.out.println("Entre com o cpf do cliente: ");
        cpf = scanner.nextInt();

        if(crtP.realizaPedidoDelivery(numero, descricao, valorEntrega, cpf))
            System.out.println("Pedido realizado com sucesso!");

    }

    /*private void exibeCliente(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Digite o cpf do cliente: ");
        int cpf = scanner.nextInt();
        Cliente c =crtC.buscaCliente(cpf);
    }*/




}

