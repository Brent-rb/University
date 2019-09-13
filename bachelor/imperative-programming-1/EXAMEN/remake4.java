//remake4.java

//Oef 14.12

class remake5 {
	public static void main(String[] args) {
		String input = args[0];
		int number = toNumber(input);

		System.out.println("" + number);
	}

	static int toNumber(String input) {
		int number;
		if(input.length() <= 0)
			return(0);
		char c = input.charAt(0);
		int tempNum;
		c -= '0';
		tempNum = (int)(c);

		for(int i = 1; i < input.length(); i++) {
			tempNum *= 10;
		}

		number = tempNum + toNumber(input.substring(1));

		return(number);

	}
}