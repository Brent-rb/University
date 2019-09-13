//opgave13_1.java
//auteur : Brent Berghmans 1334252
//enigma codering uitbreiding


class taak13_1 {
	public static void main (String []args) {
		String givenString, encodedString = "";
		int i, n;
		if (args.length < 2)
			return;
		givenString = args[0];
		n = Integer.parseInt(args[1]);
		/*if (n < 0){
			n += 26;
			n %= 26;
		}*/
		for (i = 0; i < givenString.length(); i++) {
			if (givenString.charAt(i) >= 'a' && givenString.charAt(i) <= 'z' || givenString.charAt(i) >= 'A' && givenString.charAt(i) <= 'Z'){
				encodedString += "" + encode(givenString.charAt(i), n);
				n = ((n + (encode(givenString.charAt(i), n))) % 97);
			}
			else {
				encodedString += "" + givenString.charAt(i);
				n = ((n + givenString.charAt(i)) % 97);
			}

		}
		System.out.println(encodedString);
	}
	static char encode (char c, int n) {
		n %= 26;
		if (c >= 'A' && c <= 'Z') {
			if (c + n >= 'A' && c + n <= 'Z')
				c = (char)((int)c + n);
			else
				c = (char)( 'A' + ((c + n) - 'Z' - 1 ));
		}
		else {
			if (c + n >= 'a' && c + n <= 'z')
				c = (char)((int)c + n);
			else
				c = (char)( 'a' + ((c + n) - 'z' - 1));

		}
		return(c);
	}
}