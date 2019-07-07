import java.util.Scanner;

abstract class ContaBancaria {
  private double saldo;
  private Cliente dono;
  private double emprestimo=0;

  public abstract void aplicaJuros();

  public double getSaldo() {
    return this.saldo;
  }

  public void setSaldo(double saldo) {
    this.saldo = saldo;
  }

  public void setDono(Cliente dono) {
    this.dono = dono;
  }

  public Cliente getDono() {
    return this.dono;
  }

  public void deposita(double valor) {
    double saldo = getSaldo();
    setSaldo(saldo+valor);
  }

  public void saque(double valor) {
    double saldo = getSaldo();
    if(valor <= saldo) setSaldo(saldo-valor);
    else System.out.println("Você não possui saldo suficiente para sacar este valor!");
  }

  public double getEmprestimo() {
    return this.emprestimo;
  }

  public void setEmprestimo(double emprestimo) {
    if(emprestimo !=0) {
      double saldo = getSaldo();
      setSaldo(saldo+emprestimo);
    }
    System.out.println("Empréstimo já realizado!");
    this.emprestimo = emprestimo;
  }

  public void quitaEmprestimo() {
    double saldo = getSaldo();
    double emprestimo = getEmprestimo();
    if((saldo) >= emprestimo) {
      setEmprestimo(0);
      setSaldo(saldo - emprestimo);
    }
    else {
      System.out.println("Você não possui saldo suficiente para quitar o empréstimo!");
    }
  }
}

class ContaCorrente extends ContaBancaria {
  public ContaCorrente(int saldo, Cliente dono) {
    setSaldo(saldo);
    setDono(dono);
  }

  public void aplicaJuros() {
    double emprestimo = getEmprestimo();
    double saldo = getSaldo();
    setSaldo(saldo-(emprestimo*0.03));
  }
}

class ContaPoupanca extends ContaBancaria {
  public ContaPoupanca(int saldo, Cliente dono) {
    setSaldo(saldo);
    setDono(dono);
  }

  public void aplicaJuros() {
    double saldo = getSaldo();
    setSaldo(saldo*(1.05));
  }
}

class Cliente {
  private ContaBancaria conta;
  private int id, senha;
  private String nome;
  private boolean tipoConta;

  public Cliente(String nome, int id, int senha, boolean tipoConta) {
    setNome(nome);
    setSenha(senha);
    setId(id);
    setTipoConta(tipoConta);
    if(tipoConta) {
      setConta(new ContaCorrente(0, this));
    }
    else {
      setConta(new ContaPoupanca(0, this));
    }
  }
  
  public boolean getTipoConta() {
    return this.tipoConta;
  }

  public void setTipoConta(boolean tipoConta) {
    this.tipoConta = tipoConta;
  }

  public int getSenha() {
    return this.senha;
  }

  public void setSenha(int senha) {
    this.senha = senha;
  }

  public void setConta(ContaBancaria conta) {
    this.conta = conta;
  }

  public ContaBancaria getConta() {
    return this.conta;
  }

  public void setNome(String nome) {
    this.nome = nome;
  }

  public String getNome() {
    return this.nome;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return this.id;
  }
}

class Main {
  static int nClientes=0;
  
  public static int cadastro(Cliente[] clientes) {
    Scanner scanner = new Scanner(System. in);
    System.out.println("\nDigite o nome do cliente: ");
    String inputString = scanner.nextLine();
    
    int senha;
    System.out.println("Senha: "); 
    senha = Integer.parseInt(System.console().readLine());

    int tipoConta;
    System.out.println("Digite 1- Corrente 0- Poupança: ");
    tipoConta = Integer.parseInt(System.console().readLine());

    if(tipoConta == 1) clientes[nClientes] = new Cliente(inputString, 0, senha, true);
    else clientes[nClientes] = new Cliente(inputString, 0, senha, false);

    System.out.println("\nNova conta criada. Nº: " + nClientes + " - Nome: " + inputString + "\n");

    nClientes++;

    return nClientes-1;
  }

  public static void pulaMes(Cliente[] clientes) {
    int nClientes = clientes.length;
    for(int i=0; i<nClientes; i++) {
      ContaBancaria conta = clientes[i].getConta();
      conta.aplicaJuros();
    }
  }

  public static void showMenu(int nConta, Cliente[] clientes){
    int opcao = 0;
    ContaBancaria conta = clientes[nConta].getConta();
    if(clientes[nConta].getTipoConta() == true) {
      do {
        System.out.println("\nNome: " + clientes[nConta].getNome());
        System.out.println("Nº da Conta: 0" + clientes[nConta].getId());
        System.out.println("Saldo: R$" + (conta.getSaldo()) + " (Emprestimo: R$" + conta.getEmprestimo() + ")");
        System.out.println("\nO que voce deseja?");
        System.out.println("1- Realizar Depósito");
        System.out.println("2- Realizar Saque");
        System.out.println("3- Pedir Empréstimo");
        System.out.println("4- Quitar Empréstimo");
        System.out.println("5- Pular o mês");
        System.out.println("6- Sair");

        opcao = Integer.parseInt(System.console().readLine());
        int valor;
        switch(opcao){
          case 1:
            System.out.println("\nQuanto voce deseja depositar?");
            valor = Integer.parseInt(System.console().readLine());
            conta.deposita(valor);
            break;
          case 2:
            System.out.println("\nQuanto voce deseja sacar?");
            valor = Integer.parseInt(System.console().readLine());
            conta.saque(valor);
            break;
          case 3:
            System.out.println("\nQual o valor do empréstimo?");
            valor = Integer.parseInt(System.console().readLine());
            conta.setEmprestimo(valor);
            break;
          case 4:
            conta.quitaEmprestimo();
            break;
          case 5:
            pulaMes(clientes);
            break;
          case 6:
            break;
          default:
            System.out.println("Opção Inválida!");
            break;
        }
      } while(opcao!=6);
    }
    else {
      do {
        System.out.println("\nNome: " + clientes[nConta].getNome());
        System.out.println("Nº da Conta: 0" + clientes[nConta].getId());
        System.out.println("Saldo: R$" + conta.getSaldo());
        System.out.println("\nO que voce deseja?");
        System.out.println("1- Realizar Depósito");
        System.out.println("2- Realizar Saque");
        System.out.println("3- Pular o mês");
        System.out.println("4- Sair");

        opcao = Integer.parseInt(System.console().readLine());
        int valor;
        switch(opcao){
          case 1:
            System.out.println("\nQuanto voce deseja depositar?");
            valor = Integer.parseInt(System.console().readLine());
            conta.deposita(valor);
            break;
          case 2:
            System.out.println("\nQuanto voce deseja sacar?");
            valor = Integer.parseInt(System.console().readLine());
            conta.saque(valor);
            break;
          case 3:
            System.out.println("\n1 Mês pulado?");
            pulaMes(clientes);
            break;
          case 4:
            break;
          default:
            System.out.println("Opção Inválida!");
            break;
        }
      } while(opcao!=4);
    }
  }



  public static void main(String[] args) {
    Cliente[] clientes = new Cliente[3];
    // clientes[0] = new Cliente("Guilherme", 0, 654321, true);
    // clientes[1] = new Cliente("Sabrina", 1, 123, false);
    // cadastro(clientes);
    
    int entrada;
    while(true) {
      System.out.println("Bem vindo ao Banco CC!");
      System.out.println("1- Cadastrar cliente");
      System.out.println("2- Deletar cliente");
      System.out.println("3- Logar");
      entrada = Integer.parseInt(System.console().readLine());
      switch(entrada) {
        case 1:
          cadastro(clientes);
          break;
        case 2:
          break;
        case 3:
          System.out.println("Informe o número de conta:");
          entrada = Integer.parseInt(System.console().readLine());
          if(nClientes>0) {
            for(int i=0;i<nClientes;i++) {
              if(clientes[i] != NULL && clientes.getId() == entrada) showMenu(entrada, clientes);
            }
          }
          else {
            System.out.println("Não temos nenhuma conta cadastrada. Seja o primeiro!");
          }
          break;
      }
    }
  }
}
