//opgave12_7.java
//Schrijf een programma dat een rij van N strings inleest, waarbij N een constante is,
//en vervolgens voor elke string uitschrijf in welke andere string deze string voorkomt als substring
//Auteur: Brent Berghmans 1334252


import tio.*;

class opgave12_7 {
	public static void main(String [] args) {
		//Klaarzetten tabel
		int input;
		System.out.println("Geef N");
		input = Console.in.readInt();
		String table[] = new String [input];
		String table2[];
		//variabelen declareren
		int i, j, k, l, m, amountSub = 0;
		String searchS, findS = "", sameS = "";
		boolean first = true, found = false;
		//strings inlezen
		for (i = 0; i < table.length ; i++) {
			System.out.println("Geef een string in");
			table[i] = Console.in.readLine();
		}
		//gedaan met inlezen
		for (i = 0; i < table.length ; i++) {
			searchS = table[i];
			first = true;
				found = false;
			//System.out.println("Search is " + table[i]);
			for (j = i + 1 ; j < table.length; j++) {
				findS = table[j];
				//System.out.println("Find is " + findS);
				
				//substring die we moeten zoeken einde 


				//begin zoeken
				for (k = 0; k < findS.length(); k++) {

					//als een overeenkomstige letter gevonden is doe dit
					if (searchS.charAt(0) == findS.charAt(k)) {
						//System.out.println("k is " + k + " char is " + findS.charAt(k));

						//controleer opeenvolgende letters
						for (l = 0, m = k; l < searchS.length() && k < findS.length() && (searchS.charAt(l) == findS.charAt(m)); m++, l++) {
							sameS += "" + findS.charAt(m);
							//System.out.println("Same is " + sameS);
						}

						//als de substring gevonden is 
						if (sameS.length() == searchS.length()) {
							if (first) {
								System.out.print("" + searchS + " is een substring van "+ findS);
								first = false;
								found = true;
								break;
							}
							else
								System.out.print(", " + findS);
						}

						//reset van same string 
						sameS = "";
					}
					//einde als overeenkomstige letter gevonden
				}
				
			}
			if(found) {
					System.out.println(".");
				}
				else
					System.out.println("" + searchS + " is geen substring.");
		}
	}
}