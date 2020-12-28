/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aufgabe3.scotlandYard;

/**
 * @author Vlad B
 * @since 28.12.2020
 * @param <V> Knotentyp.
 */
public interface Heuristic<V> {
	/**
	 * Schätzt die Kosten (Distanz) von u nach v ab.
	 * @param u
	 * @param v
	 * @return Geschätzte Kosten.
	 */
	double estimatedCost(V u, V v);
}
