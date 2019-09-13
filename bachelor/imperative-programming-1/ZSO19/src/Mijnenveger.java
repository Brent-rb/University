import tio.*;
import be.uhasselt.gui.*;
import be.uhasselt.util.*;


/**
 * Beste Mijnenveger ever?
 *     
 *    @author Brent Berghmans
 */
public class Mijnenveger {

	/** Indicator voor GUI-mode. */
	static boolean gui;
	static boolean [][] mineField;
	static boolean [][] explored;

		
	/**
	 * Aanroeppunt van het programma.
	 *
	 *     @param args  Niet-leeg indien GUI-mode.
	 */
	public static void main(String [] args) {
		//Declareren van variabelen
		boolean standard = false;
		int number, minesAmount;
		String string;
		int []pos;



		//Kijk of er argumenten zijn meegegeven 
		if(args.length >= 1) {
			//Als er 1 argument is ingegeven is het zowiezo de gui of cmd
			//Naar kleine letters omzetten om alle HoOfDlEttEr mogelijkheden niet te hoeven testen
			args[0] = toLow(args[0]);
			//Testen of het gui of cmd is
			if(args[0].equals("gui"))
				gui = true;
			else if(args[0].equals("cmd"))
				gui = false;
		}
		//Als er geen argumenten zijn, vragen of ze gui of cmd willen
		else {
			//Blijf vragen tot een juiste input
			do {
				System.out.println("Voor GUI vul 1 in; voor CMD vul 2 in");
				number = Console.in.readInt();
				if(number == 1)
					gui = true;
				else if(number == 2)
					gui = false;
			} while(number != 1 && number != 2);
		}
		//Als er 2 argumenten zijn standaard veld testen
		if(args.length == 2) {
			args[1] = toLow(args[1]);
			if(args[1].equals("stdfield"))
				standard = true;
			else
				standard = false;
		}
		


		//Dimensies opvragen als standaard op false staat
		if(!standard) {
			//blijf vragen tot we een juiste input krijgen
			do {
				System.out.println("Geef de dimensies: aantalRijen,aantalKolommen");
				pos = getPosText();
			} while (pos.length < 2 || pos[0] <= 0 || pos[1] <= 0);
			//Aantal mijnen opvragen
			System.out.println("Geef het aantal mijnen");
			minesAmount = Console.in.readInt();

			//mineField willekeurig genereren aan de hand van opgevraagde paramters
			mineField = EpicLibrary.generateBoolTable(pos[0],pos[1], minesAmount);
			//Explored dezelfde dimensies als mineField geven en aangezien boolean tabellen standaard op false staan moeten we geen initialisering doen
			explored = new boolean [pos[0]][pos[1]];

		}
		//Als standaard wel aan staat -> standaard tabel initialiseren
		else {
			mineField = new boolean[5][9];
			mineField[0][0] = true;
			mineField[0][7] = true;
			mineField[0][8] = true;
			mineField[1][7] = true;
			mineField[1][8] = true;
			mineField[2][1] = true;
			mineField[3][1] = true;
			mineField[3][7] = true;
			mineField[3][8] = true;
			mineField[4][7] = true;
			explored = new boolean[5][9];
		}



		//Het spel starten
		start();
	}


	/**
	 * Start het spel.
	 */
	static void start() {
		//Variabelen declareren
		int []pos;
		int row, column;
		long hours, minutes, secs;
		//Een String tabel aanmaken met daarin de waarde van lege cellen en '*' als mijnen.
		String [][]calcField = calculateField();


		
		//Als we in gui-modus zitten --> ImageGrid maken, initialiseren en tonen
		if(gui) {
				//ImageGrid aanmaken met hoogte en breedte gebasseerd op het mineField
				ImageGrid.createGrid(mineField.length, mineField[0].length, 30, 30);
				//Image path zetten
				ImageGrid.setImagePath("./images");
				//Elke rij afgaan
				for(row = 0; row < mineField.length; row++) {
					//Elke kolom afgaan 
					for(column = 0; column < mineField[row].length; column++) {
						//Alle cellen initialiseren met metalwall.png
						ImageGrid.addImage(row, column, "metalwall.png");
					}
				}
				//ImageGrid tonen
				ImageGrid.showGrid();
			}



		//Klok starten 
		StopWatch.start();
		//Zolang niet alle lege vakken explored zijn --> blijven spelen
		while(EpicLibrary.countTrue(explored) + EpicLibrary.countTrue(mineField) != (mineField.length * mineField[0].length)) {
			//Het leeg veld uitprinten
			printField(calcField);
			if(!gui)
				System.out.println();
			do {
				pos = getPos();
				row = pos[0];
				column = pos[1];
			} while(!(EpicLibrary.inBounds(mineField, pos[0], pos[1])));
			//Explored plaats op true zetten
			explored[row][column] = true;
			//Controlen of die plek leeg is, zo ja de Flood activeren
			if(checkMineField(row, column).equals("0"))
				checkFlood(row, column);

			//Als het bom is stoppen en de tijd afprinten
			if (mineField[row][column]) {
				StopWatch.stop();
				secs = StopWatch.getElapsedTimeSecs();
				minutes = secs / 60;
				secs %= 60;
				hours = minutes / 60;
				minutes %= 60;
				printField(calcField);
				System.out.println();
				System.out.println("Kabooooooooom: You exploded :( in: " + hours + "h " + minutes + "m " + secs + "s");
				System.out.println();
				//stoppen
				return;
			} 
		}
		//Als het gedaan is de eind tabel afprinten en de tijd afprinten.
		StopWatch.stop();
		secs = StopWatch.getElapsedTimeSecs();
		minutes = secs / 60;
		secs %= 60;
		hours = minutes / 60;
		minutes %= 60;


		if(gui)
			printFieldGUI(calcField, true);
		else
			printFieldText(calcField, true);


		System.out.println();
		System.out.println("Congratulations my good sir, thou be most victorious at thy game and tho performed it in: " + hours + "h " + minutes + "m " + secs + "s");
		//stoppen
		return;
	}
	

	/**
	* Een functie die de flood gaat controleren
	* @param checkRow : de rij die we controleren
	* @param checkColumn : de kolom die we controleren
	*/
	static void checkFlood(int checkRow, int checkColumn) {
		int row, column;
		boolean inbound = EpicLibrary.inBounds(mineField, checkRow, checkColumn);

		if(!inbound)
			return;

		if(!(checkMineField(checkRow, checkColumn).equals("*"))) {
			explored[checkRow][checkColumn] = true;

			if(!(checkMineField(checkRow, checkColumn).equals("0")))
				return;

			for(row = checkRow - 1; row <= checkRow + 1; row++) {
				for(column = checkColumn - 1; column <= checkColumn + 1; column++) {
					if(row != checkRow || column != checkColumn)
						if(EpicLibrary.inBounds(mineField, row, column) && (!(explored[row][column])))
							checkFlood(row, column);
				}
			}
		}
		else 
			return;
		return;
	}


	/**
	*Vult de tabel calcField op 
	*@return De ingevulde tabel
	*/
	static String[][] calculateField() {
		//variabelen declareren
		int row, column;
		String [][]calcField = new String [mineField.length][mineField[0].length];


		//Elke rij afgaan
		for(row = 0; row < calcField.length; row++) {
			//Elke kolomn van de rij afgaan
			for(column = 0; column < calcField[row].length; column++) {
				//Functie oproepen die ons de waarde terug geeft
				calcField[row][column] = checkMineField(row, column);
			}
		}
		return(calcField);
	} 
	
	/**
	 * Geeft het rij- en kolomnummer terug in tabel van grootte 2.
	 *
	 *     @return [rijnummer, kolomnummer]
	 */
	static int[] getPos() {
		if (gui)
			return getPosGUI();
		else {
			System.out.println("Geef de positie: rij,kolom");
			return getPosText();
		}
		
	}

	
	/**
	 * Geeft het rij- en kolomnummer terug in tabel van grootte 2 (via GUI).
	 *
	 *     @return [rijnummer, kolomnummer]
	 */
	static int[] getPosGUI() {
		int []pos = new int [2];
		ImageGrid.waitForClick();
		pos[0] = ImageGrid.getLastClickedRow();
		pos[1] = ImageGrid.getLastClickedColumn();
		return pos;
	}
	
	
	/**
	 * Geeft het rij- en kolomnummer terug in tabel van grootte 2 (via tekstinvoer).
	 *
	 *     @return [rijnummer, kolomnummer]
	 */
	static int[] getPosText() {
		String input;
		int []pos = new int[2];
		int i;
		input = Console.in.readLine();
		pos = EpicLibrary.findNumbers(input);
		return(pos);
	}

	
	
	/**
	 * Print het mijnenveld af.
	 * @param calcField : De tabel die we gaan afdrukken.
	 */
	static void printField(String[][] calcField) {
		if (gui)
			printFieldGUI(calcField, false);
		else 
			printFieldText(calcField, false);

	}


	/**
	 * Geeft het mijnenveld grafisch weer.
	 * @param calcField : De tabel die we gaan afdrukken
	 * @param all : Als all op true staat print die alles af (enkel nodig voor game over).
	 */
	static void printFieldGUI(String [][] calcField, boolean all) {
		int row, column;
		String number;
		ImageGrid.clear();
		for(row = 0; row < mineField.length; row++) {
			for(column = 0; column < mineField[row].length; column++) {
				if(explored[row][column] || all) {
					number = calcField[row][column];
					if(number.equals("0"))
						ImageGrid.addImage(row, column, "metalhole.png");
					else if(number.equals("*"))
						ImageGrid.addImage(row, column, "nxx.png");
						//ImageGrid.addImage(row, column, "cage.jpeg");
					else 
						ImageGrid.addImage(row, column, "n" + number + ".png");
				}
				else
					ImageGrid.addImage(row, column, "metalwall.png");
			}
		}
		ImageGrid.refresh();
		return;
	}

	/**
	*Check of het vakje een mijn is anders gaat het de buren berekenen
	* @param row : de rij van de plek die we controleren
	* @param column : de kolom van de plek die we controlen
	* @return een cijfer als hij buren heeft, spatie als hij geen buren heeft en een * als het een mijn is.
	*/
	static String checkMineField(int row, int column) {
		String number;
		if(mineField[row][column])
			return("*");
		else {
			number = countMines(row, column);
			if(number.equals(0))
				return(" ");
			else
				return("" + number);
		}
	}

	/**
	*Telt het aantal mijnen rond een vakje
	*@param checkRow : de rij die we gaan controleren
	*@param checkColumn : de kolom die we gaan controleren
	*@return Een cijfer in string vorm.
	*/
	static String countMines(int checkRow, int checkColumn) {
		int row, column, amountOfMines = 0, rowStart, columnStart;
		if(checkRow == 0)
			rowStart = 0;
		else
			rowStart = checkRow - 1;
		if(checkColumn == 0)
			columnStart = 0;
		else
			columnStart = checkColumn - 1;
		for(row = rowStart; row < mineField.length && row <= checkRow + 1; row++) {
			for(column = columnStart; column < mineField[row].length && column <= checkColumn + 1; column++) {
				if(mineField[row][column])
					amountOfMines++;
			}
		}
		return("" + amountOfMines);
	}
	
	/**
	*Convert een string naar een string met enkel kleine letters
	*@param input Een string die we naar klein letters gaan omzetten
	*@return De geconverteerde string
	*/
	static String toLow(String input) {
		int i;
		String newString = "";
		char c;

		for(i = 0; i < input.length(); i++) {
			c = input.charAt(i);
			if(c >= 'A' && c <= 'Z')
				newString += (int)((c - 'A') + 'a');
			else
				newString += c;
		}
		return(newString);
	}

	/**
	 * Geeft het mijnenveld tekstueel weer.
	 * @param table : De tabel die we gaan afprinten
	 * @param all : als dit true is wordt alles afgeprint
	 */
	static void printFieldText (String [][]table, boolean all) {
		int n1 = table.length;
		int n2 = table[0].length;
		int row, colomn, i = 0;
		for (row = 0; row < n1; row++) {
			for(i = 0; i < n2; i++) {
				if(row == 0) {
					if (i < n2)
						System.out.print(" _____");
					if (i == n2-1) {
						System.out.println();
					}
				}
			}
			for (i = 0; i < n2; i++) {
				if (i == 0)
					System.out.print("|     |");
				else
					System.out.print("     |");
			}
			System.out.println();
			for (colomn = 0; colomn < n2; colomn++) {
				if (explored[row][colomn] || all) {
					if(colomn != n2-1)
						System.out.print("|  " + table[row][colomn] + "  ");
					else
						System.out.println("|  " + table[row][colomn] + "  |");
				}
				else {
					if(colomn != n2-1)
						System.out.print("|  ?  ");
					else
						System.out.println("|  ?  |");
				}
			}
			for (i = 0; i < n2; i++) {
				if(i == 0)
					System.out.print("|_____|");
				else
					System.out.print("_____|");
			}
			System.out.println();
		}
	}

}
