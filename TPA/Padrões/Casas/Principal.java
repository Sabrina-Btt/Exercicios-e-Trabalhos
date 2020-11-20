package casas;

import java.util.Scanner;

public class Principal {
    public static void main(String args[]){
        Scanner s = new Scanner(System.in);
        System.out.print("Escolha área da Sala: ");
        float areaSala = s.nextFloat();
        Sala sala = new Sala(areaSala);
        System.out.print("Escolha área da Cozinha: ");
        float areaCozinha = s.nextFloat();
        Cozinha cozinha = new Cozinha(areaCozinha);
        Casa c=null;
        do{
            System.out.print("Escolha material da casa: 1 - Madeira, 2 - Tijolo, 3 - Aço: ");
            int opcao = s.nextInt();
            CasaFactory cf = CasaFactory.get();
            c = cf.factory(opcao, sala, cozinha);
        }while(c == null);
        int numQuartos;
        do{
            System.out.print("Escolha número de quartos (0 - 3): ");
            numQuartos = s.nextInt();
        }while(numQuartos < 0 || numQuartos > 3);
        for(int i=0; i < numQuartos; i++){
            System.out.print("Escolha a área do quarto " + i + ": ");
            float areaQuarto = s.nextFloat();
            Quarto quarto = new Quarto(areaQuarto);
            c.addQuarto(quarto);
        }
    }
}
