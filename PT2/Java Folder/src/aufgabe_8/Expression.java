package aufgabe_8;

import java.util.Map;
import java.util.Set;

public interface Expression {
    double eval(Map<String, Double> map);
    Set<Var> getVars();

}
