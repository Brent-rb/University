//taak11_1.java
//Auteur: Brent Berghmans 1334252

class taak11_1 {
	public static void main (String[] args) {
		String givenString;
		if (args.length < 1)
			return;
		int charTable [] = new int [26];
		int highest, location = 0, i, k;
		char c;
		givenString = args[0];
		//alle letters omzetten naar kleine letters
		givenString = trim(givenString);

		//elke char van de string afgaan, als de letter - 'a' tussen nul en 25 ligt in de tabel zetten
		for (i = 0; i < givenString.length() ; i++) {
			c = givenString.charAt(i);
			charTable[c - 'a']++;
		}
		highest = charTable[0];
		for (k = 0; k < charTable.length; k++) {
			for (i = 0; i < charTable.length; i++) {
				if (charTable[i] >= highest){
					highest = charTable[i];
					location = i;
				}
			}
			if (highest > 0) {
				System.out.print("" + (char)(location + 'a'));
				highest = 0;
				charTable[location] = 0;
			}
		}
		System.out.println();
	}
	static String trim(String givenString) {
		int i;
		String newString = "";
		for (i = 0; i < givenString.length(); i++) {
			if ((int)givenString.charAt(i) >= 'a' && (int)givenString.charAt(i) <= 'z')
				newString += "" + givenString.charAt(i);
		}
		return(newString);
	}
}