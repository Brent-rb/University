//

class taak15 {
	public static void main(String [] args) {
		int i, j, counter;
		String input, tempString = "";
		boolean output, correct = true;
		//String []args2 = {"(900+(900+(900+900))" "x", "1", "30000", "(x+1)", "(x+x)", "(((3*1)+(4/3))-2)", "(0-1)", "", "()",")","+","(+)", "(+", "(3+", "x+1", "(1+y)", "(-1)", "(1+2+3)", "jelle-jonny", "(x+x)(x+x)", "(x+((x+x)+x))", "()((x+x))", "((x+x))"};
		//boolean []outputTable = {false,true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false,false,true,false,false};

		if(args.length == 0)
			return;
		//for(counter = 0; counter < args2.length ; counter++) {
		input = args[0];
		//output = outputTable[counter];
		//correct = true;
		//tempString = "";

		//Minimum lengte van een veelterm is 5 : (x+x)
		if(input.length() < 5) {
			//als het maar 1 term is de condities checken
			if(checkBrackets(input) == 0 && checkItems(input) == 1 && checkOperators(input) == 0)
				correct = true;
			else
				correct = false;
		}

		//Heel de string stukje per stukje verwerken
		while(checkItems(input) > 1 && input.length() >= 5 && correct) {
			//eerste '(' zoeken --> duid het begin van binnenste term aan, aangezien we van achter beginne te tellen
			for(i = input.length() - 1; i >= 0 && input.charAt(i) != '('; i--) {
			}
			//eerste ')' zoeken naar rechts om het einde van de binnenste term te vinden
			if(i < 0)
				correct = false;
			for(j = i; j < input.length() && correct && input.charAt(j) != ')'; j++) {
			}

			//Als dit bestaat deze term als substring nemen
			if(j + 1 <= input.length() && correct) {
				tempString = input.substring(i, j + 1);
				//System.out.println("TempString is : " + tempString);
			}
			//zo niet is het fout --> geen sluit haakje
			else
				correct = false;
			//Als deze term klopt gaan we hem uit de orginele string smijten en vervangen door x --> ((x+x)+x) --> (x+x)
			if(checkString(tempString) && correct) {
				input = input.substring(0, i) + "x" + input.substring(j+ 1);
				//System.out.println("Input is " + input);
			}
			//Als de term niet klopt is het fout
			else
				correct = false;
		}
		//System.out.println("Uiteindelijke input is " + input);
		
		//De laatste uitkomst nog eens checken
		if(checkString(input))
			correct = true;
		else if(checkItems(input) == 1 && checkBrackets(input) == 0 && checkOperators(input) == 0)
			correct = true;
		else
			correct = false;
		if(correct)
			System.out.println("1");
		else
			System.out.println("0");
	//}
	}

	static int checkItems(String input) {
		int i, amountOfItems = 0;
		char tempChar;

		//Check het items in een string 
		for(i = 0; i < input.length(); i++) {
			tempChar = input.charAt(i);
			if(tempChar == 'x' || tempChar >= '0' && tempChar <= '9') {
				while(i < input.length() && (tempChar >= '0' && tempChar <= '9')) {
					tempChar = input.charAt(i);
					i++;
					if(tempChar == 'x')
						amountOfItems++;
					
				}
				amountOfItems++;
			}
		}

		return(amountOfItems);
	}

	static int checkBrackets(String input) {
		int i, amountOfOperators = 0;
		char tempChar;

		//Check operators
		for(i = 0; i < input.length(); i++) {
			tempChar = input.charAt(i);
			if(tempChar == '(' || tempChar == ')')
				amountOfOperators ++;
		}

		return(amountOfOperators);
	}

	static int checkOperators(String input) {
		int i, amountOfOperators = 0;
		char tempChar;

		//Check operators
		for(i = 0; i < input.length(); i++) {
			tempChar = input.charAt(i);
			if(tempChar == '/' || tempChar == '*' || tempChar == '-' || tempChar == '+')
				amountOfOperators ++;
		}

		return(amountOfOperators);
	}

	static boolean checkString(String input) {
		int i;
		boolean correct = false;
		if(input.length() < 5)
			return(false);
		if(input.charAt(0) == '(') {
			if(input.charAt(1) == 'x') {
				if(input.charAt(2) == '*' || input.charAt(2) == '+' || input.charAt(2) == '/' || input.charAt(2) == '-') {
					if(input.charAt(3) == 'x') {
						if(input.charAt(4) == ')')
							correct = true;
					}
					else if(input.charAt(3) >= '0' && input.charAt(3) <= '9') {
						for(i = 3; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
						if(i< input.length() && input.charAt(i) == ')')
							correct = true;
						else
							correct = false;
					}
					else
						correct = false;
				}
				else
					correct = false;
			}
			else if(input.charAt(1) >= '0' && input.charAt(1) <= '9') {
				for(i = 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
				if(i < input.length() && (input.charAt(i) == '*' || input.charAt(i) == '/' || input.charAt(i) == '-' || input.charAt(i) == '+')) {
					if(i + 1 < input.length() && input.charAt(i + 1) == 'x') {
						if(i + 2 < input.length() && input.charAt(i + 2) == ')')
							correct = true;
						else
							correct = false;
					}
					else if (i + 1 < input.length() && input.charAt(i + 1) >= '0' && input.charAt(i + 1) <= '9') {
						for(i = i + 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
						if(i < input.length() && input.charAt(i) == ')')
							correct = true;
						else
							correct = false;
					}
				}
				else
					correct = false;
			}
			else
				correct = false;
		}
		else
			correct = false;
		return(correct);
	}
}