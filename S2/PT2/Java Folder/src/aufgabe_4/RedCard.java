package aufgabe_4;

import java.util.Random;

public class RedCard extends Card {
    public RedCard(Suit s, Rank r) {
        if (s == Suit.CLUBS || s == Suit.SPADES) {
            throw new IllegalArgumentException();
        }
        suit = s;
        rank = r;
    }

    public RedCard() {
        Random rand = new Random();
        suit = Suit.values()[rand.nextInt(2)];
        rank = Rank.values()[rand.nextInt(8)];
    }
}
