package spel.speler;

import spel.Staat;
import java.util.List;
// import java.lang.*;

/**
 * AI Speler voor vier op een rij. 
 */
public class Superspeler implements Speler {
    
    protected int volgendeZet = 0;
	protected short speler;

    /**
     * Berekent de volgende zet.
     */
    public void berekenVolgendeZet(Staat staat) {
        List<Integer> zetten = staat.mogelijkeZetten();
        int value = -1;
        int valueVolgende = 0;
        boolean first = true;

        for (int i = 0; i < zetten.size(); i++) {
            try {
                staat.zetSteen(zetten.get(i), speler);
            } catch (Exception e) {}
            value = Math.max(value, evaluate(staat, false));
            if (first ||valueVolgende > value) {
                volgendeZet = zetten.get(i);
                valueVolgende = value;
                first = false;
            }
            try {
                staat.verwijderSteen(zetten.get(i));
            } catch (Exception e) {}
        }
    }
    
    /**
     * Geeft terug wat de volgende zet is.
     */
    public int geefZet() {
        return volgendeZet;
    }


    public int evaluate(Staat staat, boolean maximize) {
        final int plusInfinity = +1;
        final int minusInfinity = -1;
        int value;
        short huidigeSpeler;
        short andereSpeler;

        int payOff = 0;
        for (int i = 0; i < staat.geefBreedte(); i++ ) {
            payOff = staat.bepaalWinnaar(i);
            if(payOff == speler)
                return 1;
        }
        if(payOff != 0)
            return (-1);

        if (speler == 1)
            andereSpeler = 2;
        else
            andereSpeler = 1;

        if(maximize) {
            value = minusInfinity;
            huidigeSpeler = speler;
        }
        else {
            value = plusInfinity;
            huidigeSpeler = andereSpeler;
        }

        List<Integer> zetten = staat.mogelijkeZetten();

        for (int i = 0; i < zetten.size(); i++) {
            try {
                staat.zetSteen(zetten.get(i), huidigeSpeler);

            } catch (Exception e) {}

            if(maximize)
                value = Math.max(value, evaluate(staat, !maximize));
            else
                value = Math.min(value, evaluate(staat, !maximize));

            try {
                staat.verwijderSteen(zetten.get(i));
            } catch (Exception e) {}
        }

        return value;
    }

	/**
	 * Stelt de speler in.
	 */
	public void zetSpeler(short speler) {
		this.speler = speler;
	}

    /**
     * Niet nodig!
     */
    public void nieuweZet(int zet) {
		// Nothing to be done.
		// This is only needed for Mens.
    }
}
