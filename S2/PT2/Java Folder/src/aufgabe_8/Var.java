package aufgabe_8;

import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

public class Var implements Expression {
    private String variable;

    /**
     * Konstruktor für eine Variable
     * @param variable
     */
    public Var(String variable) {
        this.variable = variable;
    }

    public double eval(Map<String, Double> map) {
        return map.get(variable);
    }

    public Set<String> getVars() {
        Set<String> set = new TreeSet<>();
        set.add(this.variable);
        return set;
    }

    @Override
    public String toString() {
        return this.variable;
    }
}
