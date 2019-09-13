//mirror.java
//Oef 14.16

class mirror {
	public static void main(String[] args) {
		String input = args[0];
		String mirrorString = mirror(input);

		System.out.println(mirrorString);
	}

	static String mirror(String input) {
		if(input.length() == 0)
			return("");
		char c = (char)((input.charAt(0) - 'a') + 'A');
		String newString = "" + c + mirror(substring(input)) + c;
		return(newString);
	}

	static String substring(String input) {
		String newString = "";
		if(input.length() <= 1)
			return newString;
		int i;
		for(i = 1; i < input.length(); i++) {
			newString += input.charAt(i);
		}
		return newString;
	}
}