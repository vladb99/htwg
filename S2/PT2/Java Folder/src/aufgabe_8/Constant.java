package aufgabe_8;

import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

public class Constant implements Expression {
    private double constant;

    /**
     * Konstruktor für eine Konstante
     * @param constant
     */
    public Constant(double constant) {
        this.constant = constant;
    }

    @Override
    public double eval(Map<String, Double> map) {
        return this.constant;
    }

    @Override
    public Set<String> getVars() {
        return new TreeSet<>();
    }

    @Override
    public String toString() {
        return Double.toString(this.constant);
    }
}
