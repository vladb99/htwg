package aufgabe_4;

public abstract class Card {
    public enum Suit {
        DIAMONDS, HEARTS, CLUBS, SPADES;
    }

    public enum Rank {
        SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE;
    }

    protected Suit suit;
    protected Rank rank;

    public final Suit getSuit() {
        return suit;
    }

    public final Rank getRank() {
        return rank;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append(rank).append(" of ").append(suit);
        return s.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o)
            return true;
        if (!(o instanceof Card))
            return false;
        Card c = (Card) o;
        return suit == c.suit && rank == c.rank;
    }
}
