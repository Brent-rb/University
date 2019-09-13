//opgave11_4.java

import tio.*;

class opgave11_4 {
	public static void main(String [] args) {
		String gegevenString, nieuweString ="";
		int i, aantalBom = 0;
		System.out.println("Geef een string in");
		gegevenString = Console.in.readLine();
		for (i = 0; i < gegevenString.length() ; i++) {
			if (i - 1 >= 0) {
				if (gegevenString.charAt(i - 1) == '*') 
					aantalBom++;
			}
			if (i + 1 < gegevenString.length()) {
				if (gegevenString.charAt(i + 1) == '*')
					aantalBom ++;
			}
			nieuweString += "" + (char)(aantalBom + '0');
			aantalBom = 0;
		}
		System.out.println(nieuweString);
	}
}