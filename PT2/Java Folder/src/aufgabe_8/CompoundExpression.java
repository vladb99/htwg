package aufgabe_8;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

public abstract class CompoundExpression implements Expression {
    protected List<Expression> expressions = new LinkedList<>();

    public abstract double eval(Map<String, Double> map);

    public Set<Var> getVars() {
        return null;
    }
}
