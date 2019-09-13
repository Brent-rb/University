package spel.speler;

import spel.Staat;

/**
 * AI Speler voor vier op een rij. 
 */
public class Random implements Speler {
    
    protected int volgendeZet = 0;
	protected short speler;

    /**
     * Berekent de volgende zet.
     */
    public void berekenVolgendeZet(Staat staat) {
        volgendeZet = (int)(Math.random()*staat.geefBreedte());
    }
    
    /**
     * Geeft terug wat de volgende zet is.
     */
    public int geefZet() {
        return volgendeZet;
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
