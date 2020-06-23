package aufgabe_8;

import java.util.Map;

public class Quotient extends CompoundExpression {
    private Expression exp1;
    private Expression exp2;

    public Quotient(Expression a, Expression b) {
        this.exp1 = a;
        this.exp2 = b;
    }

    @Override
    public double eval(Map<String, Double> map) {
        double var1 = exp1.eval(map);
        double var2 = exp2.eval(map);
        return var1 / var2;
    }
}
