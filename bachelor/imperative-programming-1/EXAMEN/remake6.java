//remake6.java

//oef 14.14

class remake6 {
	public static void main(String[] args) {
		String input1 = args[0], input2 = args[1];
		String mergedString = merge(input1, input2);

		System.out.println("MergedString = " + mergedString);
	}

	static String merge(String left, String right) {
		String mergedString = "";
		if(left.length() == 0 && right.length() == 0)
			return("");

		if(left.length() >= 1)
			mergedString += "" + left.charAt(0);
		if(right.length() >= 1)
			mergedString += "" + right.charAt(0);

		mergedString += merge(substring(left), substring(right));

		return mergedString;
	}

	static String substring(String input) {
		if(input.length() <= 1)
			return("");

		String newString = "";
		int i;
		for(i = 1; i < input.length(); i++) {
			newString += input.charAt(i);
		}

		return newString;
	}
}