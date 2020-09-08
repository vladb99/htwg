package aufgabe_4;

/**
 * Klasse fÃ¼r WÃ¶rter mit ihren HÃ¤ufigkeiten.
 * @author vladb
 * @since 18.04.2020
 */
public class Element<T> {
    final private T data;
    private int frequency;

    /**
     * Konstruktor.
     * @param data
     * @param f H&auml;ufgkeit
     */
    public Element(T data, int f) {
        this.data = data;
        this.frequency = f;
    }

    public T getData() {
        return data;
    }

    public int getFrequency() {
        return frequency;
    }

    public void addFrequency(int f) {
        frequency += f;
    }

    @Override
    public String toString() {
        return data + ":" + frequency;
    }
}