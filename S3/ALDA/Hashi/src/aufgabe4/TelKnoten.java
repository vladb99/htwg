package aufgabe4;

import java.util.Objects;

public class TelKnoten {
    public final int x;
    public final int y;

    public TelKnoten(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if(o == null) return false;
        if(getClass() != o.getClass()) return false;

        TelKnoten telKnoten = (TelKnoten) o;
        return this.x == telKnoten.x && this.y == telKnoten.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        return "x: " + this.x + " y: " + this.y;
    }
}
