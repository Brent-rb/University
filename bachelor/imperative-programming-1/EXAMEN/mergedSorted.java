//mergedSorted.java

class mergedSorted {
	public static void main(String[] args) {
		String input1 = args[0], input2 = args[1];
		String mergedString = mergeSorted(input1, input2);

		System.out.println(mergedString);
	}

	static String mergeSorted(String left, String right) {
		if(left.length() == 0 && right.length() == 0)
			return("");
		String newString = "";
		if(left.length() != 0 && right.length() != 0) {
			if(left.charAt(0) < right.charAt(0)) {
				newString += left.charAt(0) + mergeSorted(substring(left), right);
			}
			else {
				newString += right.charAt(0) + mergeSorted(left, substring(right));
			}
		}
		else {
			if(left.length() != 0) {
				newString += left.charAt(0) + mergeSorted(substring(left), right);
			}
			else {
				newString += right.charAt(0) + mergeSorted(left, substring(right));
			}
		}

		
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