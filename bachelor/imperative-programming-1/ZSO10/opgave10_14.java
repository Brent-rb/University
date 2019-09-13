//opgave10_14.java

import tio.*;

class opgave10_14 {
	public static void main(String[] args) {
		String gegevenString;
		System.out.println("Geef een zin in");
		gegevenString = Console.in.readLine();
		int []alfabet = new int [26];
		int i, getal;
		gegevenString = tolowercase(gegevenString);
		for (i = 0; i < gegevenString.length(); i++) {
			getal = (gegevenString.charAt(i) - 'a');
			alfabet[getal]++;
		}
		for (i = 0; i < alfabet.length; i++) {
			if (alfabet[i] != 0)
				System.out.println("het aantal " + (char)(i + 'a') + " is " + alfabet[i]);
		}
	}
	static String tolowercase (String gegevenString) {
		int i;
		String nieuweString = "";
		for (i = 0; i < gegevenString.length(); i++) {
			if (gegevenString.charAt(i) >= 'a' && gegevenString.charAt(i) <= 'z' || gegevenString.charAt(i) >= 'A' && gegevenString.charAt(i) <= 'Z') { 
				if (gegevenString.charAt(i) >= 'A' && gegevenString.charAt(i) <= 'Z')
					nieuweString += (char)((gegevenString.charAt(i) - 'A') + 'a');
				else
					nieuweString += gegevenString.charAt(i);
			 }	
		}
		return(nieuweString);
	}
}