import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

///Gabriel Azevedo, Sabrina Sampaio e Wanderley Rangel

public class Main {

    public static void main(String[] args) throws IOException {
        String path = "automato.txt";

        ArrayList<String> linha = LeitorArq.leitor(path);
        Automato a = new Automato();

        for (String s : linha) {
            if(s.startsWith("S =")){
                a.setS(Integer.parseInt(s.split("\\{")[1].split("}")[0]));
            }else if(s.startsWith("F =")){
                String valores = s.split("\\{")[1].split("}")[0];

                for(String t : valores.split(",")){
                    a.addF(Integer.parseInt(t));
                }

            }else if(s.startsWith("d(")){
                Estado e = new Estado();

                String[] info = s.split("\\(")[1].split("\\)")[0].split(",");
                e.setEstado(Integer.parseInt(info[0]));
                e.setSimbolo(info[1].charAt(0));
                e.setProx(Integer.parseInt(s.split("\\{")[1].split("}")[0]));
                a.addE(e);
            }
        }

        String cadeia;
        Scanner scanner = new Scanner(System.in);
        do {
            System.out.print("Entre com a cadeia a ser checada: ");
            cadeia = scanner.next();

            if(cadeia.equals("0"))
                break;
            if(afd(cadeia, a)){
                System.out.println("Cadeia Aceita!\n");
            }else
                System.out.println("Cadeia Recusada!\n");
        }while(!cadeia.equals("0"));

    }

    public static boolean afd(String cadeia, Automato a){
        ArrayList<Estado> estados = a.getEstados();
        int atual = a.getS();
        for(char c: cadeia.toCharArray()){
            for(Estado est: estados){
                if(atual == est.getEstado() && c == est.getSimbolo()){
                    atual = est.getProx();
                    break;
                }
            }
        }
        ArrayList<Integer> f = a.getF();
        for(int fim: f){
            if(atual == fim){
                return true;
            }
        }

        return false;
    }



}