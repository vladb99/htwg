// O. Bittel;
// 28.02.2019

package aufgabe3.scotlandYard;

import aufgabe2.*;
import aufgabe3.SYSimulation.src.sim.SYSimulation;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * Kürzeste Wege in Graphen mit A*- und Dijkstra-Verfahren.
 * @author Vlad B
 * @since 28.12.2020
 * @param <V> Knotentyp.
 */
public class ShortestPath<V> {
	
	SYSimulation sim = null;
	
	Map<V,Double> dist; // Distanz für jeden Knoten
	Map<V,V> pred; // Vorgänger für jeden Knoten
	DirectedGraph<V> graph = null;
	Heuristic<V> heuristic = null;
	List<V> path = null;
	Double distance = null;
	List<V> visited = null;

	/**
	 * Konstruiert ein Objekt, das im Graph g k&uuml;rzeste Wege 
	 * nach dem A*-Verfahren berechnen kann.
	 * Die Heuristik h schätzt die Kosten zwischen zwei Knoten ab.
	 * Wird h = null gewählt, dann ist das Verfahren identisch 
	 * mit dem Dijkstra-Verfahren.
	 * @param g Gerichteter Graph
	 * @param h Heuristik. Falls h == null, werden kürzeste Wege nach
	 * dem Dijkstra-Verfahren gesucht.
	 */
	public ShortestPath(DirectedGraph<V> g, Heuristic<V> h) {
		this.graph = g;
		this.heuristic = h;

		this.dist = new TreeMap<>();
		this.pred = new TreeMap<>();
	}

	/**
	 * Diese Methode sollte nur verwendet werden, 
	 * wenn kürzeste Wege in Scotland-Yard-Plan gesucht werden.
	 * Es ist dann ein Objekt für die Scotland-Yard-Simulation zu übergeben.
	 * <p>
	 * Ein typische Aufruf für ein SYSimulation-Objekt sim sieht wie folgt aus:
	 * <p><blockquote><pre>
	 *    if (sim != null)
	 *       sim.visitStation((Integer) v, Color.blue);
	 * </pre></blockquote>
	 * @param sim SYSimulation-Objekt.
	 */
	public void setSimulator(SYSimulation sim) {
		this.sim = sim;
	}

	/**
	 * Sucht den kürzesten Weg von Starknoten s zum Zielknoten g.
	 * <p>
	 * Falls die Simulation mit setSimulator(sim) aktiviert wurde, wird der Knoten,
	 * der als nächstes aus der Kandidatenliste besucht wird, animiert.
	 * @param s Startknoten
	 * @param g Zielknoten
	 */
	public boolean searchShortestPath(V s, V g) {
		List<V> candidates = new LinkedList<>();
		visited = new LinkedList<>(); // usage of visited list avoids using infinite

		dist.put(s, (double) 0);
		pred.put(s, null);
		candidates.add(s);

		while (!candidates.isEmpty()) {
			V first = candidates.get(0);
			V best = first;
			double cost = dist.get(first) + getHeuristicCost(first, g); // dist + heuristic

			// Search for the candidate with lowest g and h value
			for(V candidate : candidates) {
				double candidateCost = dist.get(candidate) + getHeuristicCost(candidate, g);
				if (candidateCost <= cost) {
					cost = candidateCost;
					best = candidate;
				}
			}

			// Remove best candidate from candidates and add it to the visited list
			visited.add(best);
			candidates.remove(best);

			// Print message
			System.out.println("Besuche Knoten " + best.toString() + " mit d = " + dist.get(best));

			// Did it reach the target?
			if (best.equals(g)) {
				// Set path and distance
				V node = best;
				path = new LinkedList<>();
				distance = dist.get(best);
				do {
					path.add(0, node);
					node = pred.get(node);
				} while(node != null);

				return true;
			}

			// Loop through all adjacent nodes of best
			for (V w : graph.getSuccessorVertexSet(best)) {
				if (!visited.contains(w) && !candidates.contains(w)) { // w not in the candidates and visited list
					candidates.add(w);
					dist.put(w, dist.get(best) + graph.getWeight(best, w));
					pred.put(w, best);
				} else if (candidates.contains(w)) { // update cost and predecessor if already in the candidates list and cost is lower
					if (dist.get(best) + graph.getWeight(best, w) < dist.get(w)) {
						dist.put(w, dist.get(best) + graph.getWeight(best, w));
						pred.put(w, best);
					}
				}
			}

		}
		return false;
	}

	private double getHeuristicCost(V u, V v) {
		if (heuristic == null) {
			return 0;
		}
		return heuristic.estimatedCost(u, v);
	}

	/**
	 * Liefert einen kürzesten Weg von Startknoten s nach Zielknoten g.
	 * Setzt eine erfolgreiche Suche von searchShortestPath(s,g) voraus.
	 * @throws IllegalArgumentException falls kein kürzester Weg berechnet wurde.
	 * @return kürzester Weg als Liste von Knoten.
	 */
	public List<V> getShortestPath() {
		if (path == null) {
			throw new IllegalArgumentException();
		}
		return path;
	}

	/**
	 * Liefert die Länge eines kürzesten Weges von Startknoten s nach Zielknoten g zurück.
	 * Setzt eine erfolgreiche Suche von searchShortestPath(s,g) voraus.
	 * @throws IllegalArgumentException falls kein kürzester Weg berechnet wurde.
	 * @return Länge eines kürzesten Weges.
	 */
	public double getDistance() {
		if (distance == null) {
			throw new IllegalArgumentException();
		}
		return distance;
	}

}
