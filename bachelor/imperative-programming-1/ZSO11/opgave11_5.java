//opgave11_5.java

import tio.*;

class opgave11_5 {
	public static void main(String [] args) {
		String gegevenString, wachtwoord = "";
		int n, i , random;
		String []hoofdletters;
		String []kleinletters;
		System.out.println("Geef n ");
		n = Console.in.readInt();
		hoofdletters = new String [26];
		kleinletters = new String [26];
		for (i = 0; i < hoofdletters.length ; i++) {
			hoofdletters[i] = "" + (char)('A' + i);
		} 
		for (i = 0; i < kleinletters.length; i++) {
			kleinletters[i] = "" + (char)('a' + i);
		}
		for (i = 0; i < n ; i++) {
			random = (int)((Math.random() * 3.0) + 1);
			if (random == 1) {
				wachtwoord += "" + hoofdletters[((int)(Math.random() * 26.0))];
			}
			if (random == 2) {
				wachtwoord += "" + kleinletters[(char)((int)(Math.random() * 26.0))];
			}
			if (random == 3) {
				wachtwoord += "" + (char)((Math.random()* 9) + '0') ;
			}
		}
		System.out.println(wachtwoord);
	}
}