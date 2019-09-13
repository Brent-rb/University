//test.java

class test {
	public static void main(String [] args) {
		// initialiseer dictionary
		String [] dictionary = {"jo", "jonny", "jojo", "ronny", "foutje", "bataljon", "jon"};
		// voorbeelden
		System.out.println(find(dictionary, "on", "jo"));
		System.out.println(find(dictionary, "j", "o"));
		System.out.println(find(dictionary, "on", "ny"));
		System.out.println(find(dictionary, "x", "jo"));
		System.out.println(find(dictionary, "jonny", ""));
	}

	static String find(String[] table, String a, String b) {
		int i, j, k;
		boolean aIsSub, bIsSub;
		String candidate = "", foundMatch = "";

		for(i = 0; i < table.length; i++) {
			aIsSub = checkSub(table[i], a);
			bIsSub = checkSub(table[i], b);
			if(aIsSub && bIsSub) {
				candidate = table[i];
				if((candidate.length() <= foundMatch.length()) || foundMatch.length() == 0)
					foundMatch = candidate;
			}
			
		}
		return(foundMatch);
	}

	static boolean checkSub(String input, String substring) {
		int i, j, k;
		boolean isSubstring = false;
		String testString = "";
		if(substring.length() == 0)
			return(true);
		for(i = 0; i < input.length() && !isSubstring; i++) {
			if(input.charAt(i) == substring.charAt(0)) {
				for(j = i; j < input.length() && (j - i) < substring.length() && input.charAt(j) == substring.charAt(j - i); j++) {
					testString += input.charAt(j);
				}
				//System.out.println("Teststring is: " + testString);
				if(substring.equals(testString))
					isSubstring = true;
				testString = "";
			}
		}
		return(isSubstring);
	}
}