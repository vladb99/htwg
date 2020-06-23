package aufgabe_8;

import java.util.Map;
import java.util.Set;

public class Constant implements Expression {
    private double constant;

    public Constant(double constant) {
        this.constant = constant;
    }

    @Override
    public double eval(Map<String, Double> map) {
        return this.constant;
    }

    @Override
    public Set<Var> getVars() {
        return null;
    }
}
