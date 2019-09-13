//remake3.java

//Oef 14.11

class remake3 {
	public static void main(String[] args) {
		String input = args[0];
		boolean isPalin = checkPalin(input, 0, input.length() - 1);

		if(isPalin)
			System.out.println("Het is een palindroom");
		else
			System.out.println("Fuck you");
	}

	static boolean checkPalin(String input, int begin, int end) {
		if(begin >= end)
			return(true);
		boolean isPalin = input.charAt(begin) == input.charAt(end);

		isPalin &= checkPalin(input, begin + 1, end - 1);

		return(isPalin);
	}
}