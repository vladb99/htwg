package aufgabe_8;

import java.util.Map;
import java.util.Set;

public interface Expression {
    /***
     * Wertet einen Ausdruck aus
     * @param map die jeder Variablen einen double-Wert zuordnet
     * @return den double-Wert des Ausdrucks
     */
    double eval(Map<String, Double> map);

    /***
     * @return alle Variablen eines Ausdrucks als Set zurück
     */
    Set<String> getVars();
}
