//opgave11_3.java

import tio.*;

class opgave11_3 {
	public static void main(String [] args) {
		String gegevenString, substring ="";
		String tabelString[];
		int i, j, k, lengte;
		System.out.println("Geef een string in");
		gegevenString = Console.in.readLine();
		tabelString = new String[gegevenString.length()];
		for (i = 0, j = 0 ; i < gegevenString.length(); i ++, j++) {
			while (i < gegevenString.length()) {
				substring = "" + gegevenString.charAt(i);
				if (substring.equals(" ") || substring.length() < 1) {
					i++;
				}
				else 
					break;
			}
			tabelString[j] = substring;
		}
		lengte = tabelString.length;
		j = 0;
		for (k = 0; k < lengte ; k++) {
			for (i = 0; i < lengte ; i++){
				for (j =  k ; j <= i; j++) {
					System.out.print(tabelString[j]);
					if (j == i)
						if (k + 1 != lengte)
							System.out.print(",");
						else 
							System.out.println();
				}
				
			}
		}
	}
}