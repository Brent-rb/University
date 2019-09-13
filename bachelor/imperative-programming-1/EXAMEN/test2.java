//test2.java

class test2 {
	public static void main(String[] args) {
		System.out.println(insertDings("Jaba is heel plezant", 5));
		System.out.println(insertDings("De koetsier poetst de postkoets met postkoetspoets", 8));
		System.out.println(insertDings("eenie meenie", 6));
	}

	public static String insertDings(String text, int max) {
		String newString = "";
		final String DING = "<ding>";
		final String NEWLINE = "\n";

		int i, j, k;

		for(i = 0; i < text.length();) {
			for(j = 0; j < max; j++, i++) {
				newString += "" +text.charAt(i);
			}
			newString += DING;
			if(isLetter(text.charAt(i - 1))) {
				for(i = i; i < text.length() && isLetter(text.charAt(i)); i++) {
					newString += text.charAt(i);
				}
			}
			if(i < text.length() && text.charAt(i) == ' ')
				i++;
			newString += NEWLINE;
		}

		return(newString);

	}

	static boolean isLetter(char c) {
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return(true);
		else
			return(false);
	}
}