//opgave12_1.java
//auteur : Brent Berghmans 1334252
//enigma codering


class taak12_1 {
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
				n %= 26;
				encodedString += "" + encode(givenString.charAt(i), n);
			}
			else {
				encodedString += "" + givenString.charAt(i);
			}
			n++;
		}
		System.out.println(encodedString);
	}
	static char encode (char c, int n) {
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