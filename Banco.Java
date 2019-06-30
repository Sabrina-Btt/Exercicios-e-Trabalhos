public static void showMenu(int nConta){
 int opcao;
 do{
   System.out.println("Saldo: " + vet[nConta].getSaldo());
   System.out.println("O que voce deseja?");
   System.out.println("1- Realizar Deposito");
   System.out.println("2- Realizar Saque");
   System.out.println("3- Realizar Emprestimo");
   System.out.println("4- Sair");
 
   opcao = Console.readInt("Opção -> ");
   switch(opcao){
     case 1: 
           System.out.println("Quanto voce deseja depositar?");
           int valor = Console.readInt("Valor -> ");
           rDeposito(valor);
           break;
     case 2:
           System.out.println("Quanto voce deseja sacar?");
           int valor = Console.readInt("Valor -> ");    
           rSaque(valor);
     case 3:
           System.out.println("Qual o valor do emprestimo?");
           int valor = Console.readInt("Valor -> ");    
           rEmprestimo(valor);     
     default:
			System.out.println("Opção Inválida!");
			break;
   
   }       


  }while(opcao!=4);

}

class Main {
  public static void main(String[] args) {
    int vet[] = new int [10];

    System.out.println("Bem vindo ao Banco CC!");
    System.out.println("Informe seu numero de conta:");
    nConta = Console.readInt("-> ");
    showMenu(nConta);
    
  }
}
