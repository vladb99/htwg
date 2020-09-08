package aufgabe_8;

import java.util.*;

public abstract class CompoundExpression implements Expression {
    protected Expression exp1;
    protected Expression exp2;
    protected char symbol;

    public abstract double eval(Map<String, Double> map);

    public Set<String> getVars() {
        Set<String> finalSet = new TreeSet<>(exp1.getVars());
        finalSet.addAll(exp2.getVars());
        return finalSet;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("(");
        sb.append(exp1);
        sb.append(" ");
        sb.append(symbol);
        sb.append(" ");
        sb.append(exp2);
        sb.append(")");
        return sb.toString();
    }
}
