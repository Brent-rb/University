class taak14_1 {
	public static void main(String[] args) {
		long input, i, som = 0;
		String binaryNumber;
		if (args.length < 1)
			return;
		
		input = Integer.parseInt(args[0]);
		
		for (i = 0; i <= input; i++) {
			if(checkPalindroom(("" + i))) {
				binaryNumber = toBin(i);
				if(checkPalindroom(binaryNumber)) {
					som += i;
				}
			}
		}
		System.out.println(som);
	}

	static String toBin(long input) {
		int i;
		String binString = "";
		while (input / 2 != 0) {
			binString = "" + (input % 2) + binString;
			input /= 2;
		}
		binString = "" + (input % 2) + binString;
		input /= 2;
		return(binString);
	}

	static Boolean checkPalindroom(String input) {
		int begin, end;
		boolean isPalin = true;
		for(begin = 0, end = input.length() - 1; begin < end && isPalin; begin++, end--) {
			isPalin = (input.charAt(begin) == input.charAt(end));
		}
		return(isPalin);
	}
}