//opgave15_8_2.java

import tio.*;

class opgave15_8_2 {
	public static void main(String[] args) {
		String givenString, givenString2;
		int distance = 0;
		System.out.println("Geef string 1");
		givenString = Console.in.readLine();
		System.out.println("Geef string 2");
		givenString2 = Console.in.readLine();
		distance += checkWrong(givenString, givenString2);
		System.out.println("Distance is " + distance);
	}

	static int checkWrong(String string1, String string2) {
		int distance = 0;
		int extra = 0;
		
		if (string1.length() < string2.length()) {
			extra = string2.length() - string1.length();
			string2 = string2.substring(0,string1.length());
		}
		if (string1.length() > string2.length()) {
			extra = string1.length() - string2.length();
			string1 = string1.substring(0, string2.length());
		}
		int length = string1.length();
		if(string1.length() == 0)
			return(0);
		if(string1.charAt(0) != string2.charAt(0)) {
			distance = 1;
		}
		distance += checkWrong(string1.substring(1, length), string2.substring(1, length));
		return(distance + extra);
	}
}