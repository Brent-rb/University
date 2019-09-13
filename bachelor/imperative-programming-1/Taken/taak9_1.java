//taak9_1.java

class Taak {
	public static void main(String[] args) {
		String gegevenString, linkerString = "", rechterString = "";
		int i,j;
		boolean speler2wint = false, speler1wint = false, rock = false, scissors = false, lizard = false, spock = false, paper = false, tie = false;
		if (args.length < 2) {
			System.out.println("Usage: java Taak symbool symbool");
			return;
		}
		linkerString = args[0];
		rechterString = args[1];
		linkerString = tolowercase(linkerString);
		rechterString = tolowercase(rechterString);
		if (!(linkerString.equals("rock") || linkerString.equals("paper") || linkerString.equals("lizard") || linkerString.equals("spock") || linkerString.equals("scissors"))){
			System.out.println("What’s that? Please use a real symbol!");
			return;
		}
		if (!(rechterString.equals("rock") || rechterString.equals("paper") || rechterString.equals("lizard") || rechterString.equals("spock") || rechterString.equals("scissors"))){
			System.out.println("What’s that? Please use a real symbol!");
			return;
		}
		if (linkerString.equals("rock") || rechterString.equals("rock"))
			rock = true;
		else
			rock = false;
		if (linkerString.equals("paper") || rechterString.equals("paper"))
			paper = true;
		else
			paper = false;
		if (linkerString.equals("scissors") || rechterString.equals("scissors"))
			scissors = true;
		else
			scissors = false;
		if (linkerString.equals("spock") || rechterString.equals("spock"))
			spock = true;
		else
			lizard= false;
		if (linkerString.equals("lizard") || rechterString.equals("lizard"))
			lizard = true;
		else 
			lizard = false;
		if (rock) {
			if (spock || paper) {
				if (linkerString.equals("paper") || linkerString.equals("spock"))
					speler1wint = true;
				else
					speler2wint = true;
			}
			else {
				if (linkerString.equals("rock")) {
					if (rechterString.equals("rock"))
						tie = true;
					else
						speler1wint = true;
				}
				else
					speler2wint = true;
			}
		}
		if (paper) {
			if (scissors || lizard) {
				if (linkerString.equals("lizard") || linkerString.equals("scissors"))
					speler1wint = true;
				else
					speler2wint = true;
			}
			else {
				if (linkerString.equals("paper")) {
					if (rechterString.equals("paper"))
						tie = true;
					else
						speler1wint = true;
				}
				else
					speler2wint = true;
			}
		}
		if (scissors) {
			if (rock || spock) {
				if (linkerString.equals("spock") || linkerString.equals("rock"))
					speler1wint = true;
				else
					speler2wint = true;
			}
			else {
				if (linkerString.equals("scissors")) {
					if (rechterString.equals("scissors"))
						tie = true;
					else
						speler1wint = true;
				}
				else
					speler2wint = true;
			}
		}
		if (lizard) {
			if (rock || scissors) {
				if (linkerString.equals("scissors") || linkerString.equals("rock"))
					speler1wint = true;
				else
					speler2wint = true;
			}
			else {
				if (linkerString.equals("lizard")) {
					if (rechterString.equals("lizard"))
						tie = true;
					else
						speler1wint = true;
				}
				else
					speler2wint = true;
			}
		}
		if (spock) {
			if (lizard || paper) {
				if (linkerString.equals("paper") || linkerString.equals("lizard"))
					speler1wint = true;
				else
					speler2wint = true;
			}
			else {
				if (linkerString.equals("spock")) {
					if (rechterString.equals("spock"))
						tie = true;
					else
						speler1wint = true;
				}
				else
					speler2wint = true;
			}
		}
		if (tie)
			System.out.println("It’s a tie (the non-clothing kind)!");
		else {
			if(speler1wint)
				System.out.println("Player 1 wins!");
			else
				System.out.println("Player 2 wins!");
		}
	}

	static String tolowercase (String gegevenString) {
		String nieuweString = "";
		int i;
		for (i = 0; i < gegevenString.length(); i++) {
			if (gegevenString.charAt(i) >= 'A' && gegevenString.charAt(i) <= 'Z')
				nieuweString += "" + (char)((gegevenString.charAt(i) - 'A') + 'a');
			else 
				nieuweString += "" + gegevenString.charAt(i);
		}
		return(nieuweString);
	}
}
