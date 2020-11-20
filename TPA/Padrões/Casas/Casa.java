package casas;

import java.util.ArrayList;

public class Casa {
    private final ArrayList<Comodo>   comodos = new ArrayList<Comodo>();
    
    public Casa(Sala s,Cozinha c){
        comodos.add(s);
        comodos.add(c);
    }

    public void addSala(Sala s){
        if(numComodos(Sala.class) < 2)
            comodos.add(s);
    }
    
    public void addQuarto(Quarto q){
        if(numComodos(Quarto.class) < 3)
            comodos.add(q);
    }
    
    protected int numComodos(Class cl){
        int count = 0;
        for(Comodo c : comodos){
            if(cl.isInstance(c))
                count++;
        }
        return count;
    }

    public static Casa factory(int material, Sala sala, Cozinha cozinha){
        if(material == 1){
            return new CasaMadeira(sala, cozinha);

        }
        else if(material == 2){
            return new CasaTijolo(sala, cozinha);

        }
        else if(material == 3){
            return new CasaAco(sala, cozinha);

        }
        return null;
    }
}
