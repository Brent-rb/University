package spel;

import java.util.Iterator;
import java.util.List;


public interface Staat {
	
	/**
	 * Maakt een kopie van deze staat. 
	 * @return	
	 */
	public abstract Staat copy();
	
	// ============================================================
	// CHECKING
	// ============================================================
	/**
	 * Controleert of een kolom vol is.
	 * 
	 * @param kolom
	 *            kolom die gecheckt wordt
	 * @return True als de kolom vol is, False anders
	 */
	public abstract boolean isKolomVol(int kolom) throws BuitenBordExceptie;
	
	/**
	 * Geeft een lijst terug van de kolommen die nog niet vol zijn.
	 */
	public abstract List<Integer> mogelijkeZetten();
	
	/**
	 * Controleert of de gegeven positie bezet wordt door speler 1.
	 * 
	 * @return True als bezet door speler 1
	 * @throws BuitenBordExceptie
	 */
	public abstract boolean isBezetDoorSpeler1(int kolom, int rij)
			throws BuitenBordExceptie;
	
	/**
	 * Controleert of de gegeven positie bezet wordt door speler 2.
	 * @return True als bezet foor speler 2
	 */
	public abstract boolean isBezetDoorSpeler2(int kolom, int rij)
			throws BuitenBordExceptie;
	
	/**
	 * Is het gegeven vak vrij?
	 */
	public abstract boolean isVrij(int kolom, int rij)
			throws BuitenBordExceptie;
	
	/**
	 * Geeft terug op welke rij de hoogste steen ligt in de gevraagde kolom.
	 * @param kolom	kolom
	 * @return		hoogste steen, -1 als er geen steen ligt
	 * @throws BuitenBordExceptie 
	 */
	public abstract int hoogsteSteen(int kolom)
		throws BuitenBordExceptie;
	
	/**
	 * Bezet de gegeven speler het gegeven vak?
	 */
	public abstract boolean isBezetDoorSpeler(int kolom, int rij, short speler)
			throws BuitenBordExceptie;
	
	/**
	 * Controleert of er een vier op en rij aanwezig is, nadat op de gegeven
	 * positie een steen is geplaatst.
	 * 
	 * @param kolom
	 *            kolom waar de laatste steen is geplaatst
	 * @return vier op een rij gemaakt
	 */
	public abstract boolean spelGewonnen(int kolom);
	
	/**
	 * Bepaalt wie de bovenste steen heeft in de gegeven kolom en of deze
	 * steen deel uitmaakt van een vier op een rij. 
	 * @param kolom		kolom
	 * @return			de speler die wint, of 0 als er geen vier op een rij is
	 * 					op de aangegeven plaats.
	 */
	public abstract short bepaalWinnaar(int kolom);
	
	/**
	 * Controleert of het spel is afgelopen. 
	 * @return	speler die gewonnen heeft
	 */
	public abstract short spelGeeindigd();
	
	/**
	 * Controleert of het bord volstaat. 
	 * @return	true als het bord vol staat, false anders
	 */
	public abstract boolean bordIsVol();
	
	// ============================================================
	// STENEN PLAATSEN
	// ============================================================
	/**
	 * Dropt een steen van de gegeven speler in de gegeven kolom.
	 */
	public abstract void zetSteen(int kolom, short speler)
			throws BuitenBordExceptie, VolleKolomExceptie;
	
	/**
	 * Verwijdert de steen op de gegeven positie.
	 */
	public abstract void verwijderSteen(int kolom) throws BuitenBordExceptie,
			LegeKolomExceptie;
	
	/**
	 * Herzet alle vakken naar leeg. 
	 */
	public abstract void reset();
	
	// ============================================================
	// GETTING
	// ============================================================
	/**
	 * Geeft de breedte van het bord.
	 */
	public abstract int geefBreedte();
	
	/**
	 * Geeft de hoogte van het bord.
	 * 
	 * @return
	 */
	public abstract int geefHoogte();
	
	// ============================================================
	// ITERATORS
	// ============================================================
	/**
	 * Geeft een kolom iterator terug.
	 */
	public abstract KolomIterator kolomIterator();
	
	/**
	 * Geeft een rij iterator terug.
	 */
	public abstract RijIterator rijIterator();


	/**
	 * Iterator die over de kolommen loopt.
	 */
	public interface KolomIterator extends Iterator<KolomRijIterator> {
	    
	}

	/**
	 * Iterator die over de rijen loopt. 
	 */
	public interface RijIterator extends Iterator<RijKolomIterator> {

	}

	/**
	 * Iterator die over een gegeven kolom loopt.
	 */
	public interface KolomRijIterator extends Iterator<Short> {

	}

	/**
	 * Iterator die over een gegeven rij loopt. 
	 */
	public interface RijKolomIterator extends Iterator<Short> {

	}
}