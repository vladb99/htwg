package aufgabe_4;

import java.util.Random;

public class BlackCard extends Card {
    public BlackCard(Suit s, Rank r) {
        if (s == Suit.DIAMONDS || s == Suit.HEARTS) {
            throw new IllegalArgumentException();
        }
        suit = s;
        rank = r;
    }

    public BlackCard() {
        Random rand = new Random();
        suit = Suit.values()[rand.nextInt(2) + 2];
        rank = Rank.values()[rand.nextInt(8)];
    }
}
