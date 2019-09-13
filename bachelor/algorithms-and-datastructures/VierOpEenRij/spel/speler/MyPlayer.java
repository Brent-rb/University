package spel.speler;

import spel.speler.Speler;
import java.util.Iterator;
import java.util.ListIterator;
import java.util.List;
import spel.Staat;

public class MyPlayer implements Speler {

	private short speler;
	private int volgendeZet;
	/**
	 * De speler krijgt de staat van het bord en berekent zijn volgende zet.
	 * @param staat	staat van het bord
	 */
	public void berekenVolgendeZet(Staat staat) {
		Staat copy = staat.copy();
		Iterator<Integer> listIt = staat.mogelijkeZetten().iterator();
		int highest = 0, temp;
		boolean first = true;

		int column;
		int highestColumn = -1;
		
		while(listIt.hasNext()) {
			column = listIt.next();
			try {
				copy.zetSteen(column, speler);
			}
			catch(Exception e) {

			}
			temp = berekenAndereSpeler(copy);
			if(first || temp > highest) {
				highest = temp;
				highestColumn = column;
				first = false;
			}

			try {
				copy.verwijderSteen(column);
			}
			catch(Exception e) {

			}
		}

		volgendeZet = highestColumn;
	}

	private int berekenDezeSpeler(Staat staat) {
		Iterator<Integer> listIt = staat.mogelijkeZetten().iterator();
		int highest = 0, temp;
		boolean first = true;

		int column;
		int highestColumn = -1;
		while(listIt.hasNext()) {
			column = listIt.next();
			try {
				staat.zetSteen(column, speler);
			}
			catch(Exception e) {
				
			}
			if(staat.spelGewonnen(column)) {
				temp = 1;
			}
			else
				temp = berekenAndereSpeler(staat);
			if(temp == 1) {
				try {
					staat.verwijderSteen(column);
				}
				catch(Exception e) {
					
				}
				return 1;
			}
			if(first || highest < temp) {
				highest = temp;
				highestColumn = column;
				first = false;
			}
			try {
				staat.verwijderSteen(column);
			}
			catch(Exception e) {
				
			}
		}

		return highest;
	}

	private int berekenAndereSpeler(Staat staat) {
		Iterator<Integer> listIt = staat.mogelijkeZetten().iterator();
		short speler;
		if(this.speler == 1)
			speler = 2;
		else
			speler = 1;
		int lowest = 0, temp;
		boolean first = true;

		int column;
		int highestColumn = -1;
		while(listIt.hasNext()) {
			column = listIt.next();
			try {
				staat.zetSteen(column, speler);
			}
			catch(Exception e) {
				
			}
			if(staat.spelGewonnen(column)) 
				temp = -1;
			else
				temp = berekenDezeSpeler(staat);

			if(temp == -1) {
				try {
					staat.verwijderSteen(column);
				}
				catch(Exception e) {
					
				}
				return -1;
			}
			if(first || lowest > temp) {
				lowest = temp;
				highestColumn = column;
				first = false;
			}
			try {
				staat.verwijderSteen(column);
			}
			catch(Exception e) {
				
			}
		}

		return lowest;
	}
	
	/**
	 * De speler geeft zijn berekende zet. 
	 * @return		de volgende zet van de speler
	 */
	public int geefZet() {
		return volgendeZet;
	}


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