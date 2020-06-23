package aufgabe_8;

import java.util.Map;
import java.util.Set;

public class Var implements Expression {
    private String variable;

    public Var(String variable) {
        this.variable = variable;
    }

    public double eval(Map<String, Double> map) {
        return map.get(variable);
    }

    public Set<Var> getVars() {
        return null;
    }
}
