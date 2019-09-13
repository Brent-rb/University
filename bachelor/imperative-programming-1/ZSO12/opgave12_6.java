//opgave12_6.java
//Schrijf een programma dat nagaat of elk element van een gegenereede matrix maar op één positie voorkomt. 
//D.w.z. ga na of alle elementen in de matrix verschillend zijn.
//Dit mag niet bij de generatie van e matrix gebeuren. Je moet dit nagaan door alle elementen van de matrix te bekijken.
//Indien de matrix niet voldoet schrijf dan de posities van twee dubbels uit 
//Auteur : Brent Berghmans 1334252


import tio.*;

class opgave12_6 {
	public static void main(String [] args) {
		int input, row = 0, colomn = 0, spacesCount, i;
		String spaces;
		System.out.println("Geef de dimensies in");
		//input inlezen
		input = Console.in.readInt();
		//tabel aanmaken met input x input dimensies
		int table[][] = new int [input][input];

		//tabel invullen
		for (row = 0; row < table.length; row++) {
			for (colomn = 0; colomn < table[row].length; colomn++) {
				table[row][colomn] = (int)((Math.random() * 99999.0) + 1);
				//System.out.print(table[row][colomn]);
				/*spaces = "" + table[row][colomn];
				spacesCount = (7 - spaces.length());
				for (i = 0; i < spacesCount; i++) {
					System.out.print(" ");
				}*/
			}
			//System.out.println();
		}

		//zoekfunctie
		int searchRow = 0, searchColomn = 0, searchNum = 0;
		boolean duplicate = false;
		for (searchRow = 0; searchRow < table.length && !duplicate; searchRow++){
			//Een getal pakken van de tabel waarmee we de rest vergelijken voor een duplicaat
			for (searchColomn = 0; searchColomn < table[searchRow].length && !duplicate ; searchColomn++) {
				//We pakken het getal op de searchRow rij en searchColomn kolom
				searchNum = table[searchRow][searchColomn];
				//nu gaan we de tabel af voor een duplicaat te vinden
				for (row = searchRow; row == searchRow && !duplicate; row++){
					for (colomn = searchColomn + 1; colomn < table[row].length && !duplicate; colomn++){
						//als we een duplicaat hebben gevonden: duplicaat boolean op true zetten voor beindigen van lus en rij en kolom -1 doen voor de plaats bepaling
						//if test zodat hij niet zijn eigen als duplicaat pakt
						if(searchNum == table[row][colomn]){
							duplicate = true;
						}
					}
				}
				for (row = searchRow + 1; row < table.length && !duplicate; row++){
					for (colomn = 0; colomn < table[row].length && !duplicate; colomn++){
						//als we een duplicaat hebben gevonden: duplicaat boolean op true zetten voor beindigen van lus en rij en kolom -1 doen voor de plaats bepaling
						//if test zodat hij niet zijn eigen als duplicaat pakt
						if(searchNum == table[row][colomn]){
							duplicate = true;
						}
					}
				}
			}
		}
		row--;
		colomn--;
		searchRow--;
		searchColomn--;
		if (duplicate) {
			System.out.println("Het getal " + searchNum + " komt op (" + searchRow + "," + searchColomn + ") voor en op (" + row + "," + colomn + ") voor.");
		}
		else 
			System.out.println("Geen duplicaat gevonden");
	}
}