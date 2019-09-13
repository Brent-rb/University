package spel.speler;

import spel.Staat;
import spel.gui.ZetListener;

/**
 * De functionaliteiten de een speler moet voorzien. 
 * @author joris
 */
public interface Speler extends ZetListener {
	
	/**
	 * De speler krijgt de staat van het bord en berekent zijn volgende zet.
	 * @param staat	staat van het bord
	 */
	public void berekenVolgendeZet(Staat staat);
	
	/**
	 * De speler geeft zijn berekende zet. 
	 * @return		de volgende zet van de speler
	 */
	public int geefZet();

	/**
	 * Stelt in wat het nummer van de speler is. 1 = Speler 1, 2 = Speler 2.
	 * @param speler	de speler waarvoor we spelen
	 */
	public void zetSpeler(short speler);
}
