import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;


public class LeitorArq {

    public static ArrayList<String> leitor(String path) throws IOException {
        ArrayList<String> linhas = new ArrayList<>();
        BufferedReader buffRead = new BufferedReader(new FileReader(path));
        String linha;
        while (true) {
            linha = buffRead.readLine();
            if (linha != null) {
                linhas.add(linha);

            } else
                break;

        }
        buffRead.close();
        return linhas;
    }

}

