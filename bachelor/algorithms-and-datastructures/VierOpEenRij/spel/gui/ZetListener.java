package spel.gui;

/**
 * Luistert naar ZetObservables voor een volgende zet.  
 * @author joris
 */
public interface ZetListener {
	
	/**
	 * Een nieuwe zet is gekozen. 
	 */
	public void nieuweZet(int zet);
}
