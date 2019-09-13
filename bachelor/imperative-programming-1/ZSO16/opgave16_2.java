//opgave16_2.java
//Doel : vergelijk 2 strings recursief
//Aanpak : roep functie op met: boolean equal = compare(string1, string2) --> compare { if(string1.charAt(0) == string2.charAt(0)) equal = compare(string1.substring(1, string1.length()), string2.substring(1, string2.length()); else equal = false; return(equal)}
//Input: string1, string2
//Auteur Brent Berghmans

import tio.*; 

class opgave16_2 {
	public static void main(String [] args) {
		String string1, string2; 
		int index;
		boolean equal;

		System.out.println("Geef de eerste string");
		string1 = Console.in.readLine();
		System.out.println("Geef de tweede string");
		string2 = Console.in.readLine();
		System.out.println("Geef een index");
		index = Console.in.readInt();

		//Vergelijk functie oproepen
		equal = compare(string1, string2);

		System.out.println("Methode 1:");
		if(equal)
			System.out.println("Ze zijn gelijk");
		else
			System.out.println("Ze zijn verschillend");
		
		equal = compare2(string1, string2, index);

		System.out.println("Methode 2:");
		if(equal)
			System.out.println("Ze zijn gelijk vanaf: " + index);
		else
			System.out.println("Ze zijn verschillend vanaf: " + index);
	}

	static boolean compare(String string1, String string2) {
		boolean equal;
		if(string1.length() != string2.length())
			return(false);
		if(string1.length() > 0 && string2.length() > 0) {
			if (string1.charAt(0) == string2.charAt(0))
				equal = compare(string1.substring(1, string1.length()), string2.substring(1, string2.length()));
			else
				equal = false;
		}
		else 
			return(true);
		return(equal);
	}

	static boolean compare2(String string1, String string2, int index) {
		boolean equal;
		if(string1.length() != string2.length())
			return(false);
		if(index < string1.length()) {
			if (string1.charAt(index) == string2.charAt(index))
				equal = compare2(string1, string2, index + 1);
			else
				equal = false;
		}
		else 
			return(true);
		return(equal);
	}
}