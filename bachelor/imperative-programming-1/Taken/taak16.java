//

class taak16 {
	public static void main(String [] args) {
		int i, j, counter;
		String input, tempString = "";
		boolean output, correct = true, p, q, r, t = true, f = false;
		String i1, i2, i3;
		if(args.length < 4)
			return;
		input = args[0];
		i1 = args[1];
		i2 = args[2];
		i3 = args[3];
		if(!(checkBoolean(i1) && checkBoolean(i2) && checkBoolean(i3))) {
			System.out.println("false");
			return;
		}
			
			p = Boolean.parseBoolean(i1);
			q = Boolean.parseBoolean(i2);
			r = Boolean.parseBoolean(i3);
		
		System.out.println(checkInput(input,p,q,r));
		//testInput();
	}

	static boolean checkBoolean(String input) {
		if(input.equals("false") || input.equals("true"))
			return(true);
		else
			return(false);
	}
	static boolean checkInput(String input, boolean p, boolean q, boolean r) {
		int i, j, counter;
		char c;
		String tempString = "";
		boolean output, correct = true, t = true, f = false;
		if(input.length() == 0)
			return(false);
		input = trim(input);
		input = replace(input, p, q, r);

		//Heel de string stukje per stukje verwerken
		while(correct && input.length() != 1) {
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
			if(checkString(tempString,p,q,r) && correct) {
				input = input.substring(0, i) + calculateString(tempString, p,q,r) + input.substring(j+ 1);
				//System.out.println("Input is " + input);
			}
			//Als de term niet klopt is het fout
			else
				correct = false;
		}
		//System.out.println("Uiteindelijke input is " + input);
		
		//De laatste uitkomst nog eens checken
		if(checkFinalString(input))
			correct = true;
		else
			correct = false;
		//else if(checkItems(input) == 1 && checkBrackets(input) == 0 && checkOperators(input) == 0)
		//	correct = true;
		//else
		//	correct = false;
		
		return(correct);
	}
	static String replace(String input, boolean p, boolean q, boolean r) {
		int i;
		for(i = 0; i < input.length(); i++) {
			if(input.charAt(i) == 'p') {
				if(p)
					if(i < input.length())
						input = input.substring(0, i) + "t" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "t";
				else
					if(i < input.length())
						input = input.substring(0, i) + "f" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "f";
			}
			if(input.charAt(i) == 'q') {
				if(q)
					if(i < input.length())
						input = input.substring(0, i) + "t" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "t";
				else
					if(i < input.length())
						input = input.substring(0, i) + "f" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "f";
			}
			if(input.charAt(i) == 'r') {
				if(r)
					if(i < input.length())
						input = input.substring(0, i) + "t" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "t";
				else
					if(i < input.length())
						input = input.substring(0, i) + "f" + input.substring(i + 1);
					else
						input = input.substring(0, i) + "f";
			}
		}
		//System.out.println("Output replace is " + input);
		return(input);
	}
	static String trim(String input) {
		int i,j,k;
		String newString = "";
		//System.out.println("Input was :" + input);
		for(i = 0; i < input.length(); i++) {
			if(input.charAt(i) == 't') {
				for(j = i; j < input.length() && input.charAt(j) != 'e'; j++) {

				}
				if(j + 1 < input.length()) {
					input = input.substring(0, i) + "t" + input.substring(j + 1);
					newString += "t";
				}
				else if(j < input.length() && input.charAt(j) == 'e') {
					input = input.substring(0,i) + "t";
					newString += "t";
				}
			}
			else if(i < input.length() && input.charAt(i) == 'f') {
				for(j = i; j < input.length() && input.charAt(j) != 'e'; j++) {

				}
				if(j + 1 < input.length()){
					input = input.substring(0, i) + "f" + input.substring(j + 1);
					newString += "f";
				}
				else if(j < input.length() && input.charAt(j) == 'e') {
					input = input.substring(0,i) + "f";
					newString += "f";
				}
			} 
			else if(i < input.length() && input.charAt(i) == ' ') {
				for(j = i; j < input.length() && input.charAt(i) == ' '; j++) {
				}
				if(j < input.length()) {
					input = input.substring(0, i) + input.substring(j, input.length());
					newString += input.charAt(j);
				}
			}
			else {
				newString += input.charAt(i);
			}
		}
		//System.out.println("Output is :" + newString);
		return(newString);
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
			if(tempChar == '&' || tempChar == '|' || tempChar == '!')
				amountOfOperators ++;
		}

		return(amountOfOperators);
	}

	static String calculateString(String input, boolean p, boolean q, boolean r) {
		int i;
		boolean correct = true;
		if(input.length() == 5) {
			if(input.charAt(0) == '(') {
				if(input.charAt(1) == 't') {
					if(input.charAt(2) == '&') {
						if(input.charAt(3) == 't') {
							if(input.charAt(4) == ')')
								return("t");
							else
								return("f");
						}
						else
							return("f");
					}
					else if(input.charAt(2) == '|') {
						if(input.charAt(3) == 't' || input.charAt(3) == 'f') {
							if(input.charAt(4) == ')') 
								return("t");
							else
								return("f");
						}
						return("f");
					}
					else
						return("f");
				}
				else if(input.charAt(1) == 'f') {
					if(input.charAt(2) == '&') {
						if(input.charAt(3) == 't' || input.charAt(3) == 'f') {
							return("f");
						}
					}
					else if(input.charAt(2) == '|') {
						if(input.charAt(3) == 't') {
							if(input.charAt(4) == ')') 
								return("t");
							else
								return("f");
						}
						return("f");
					}
					else
						return("f");
				}
			}
		}
		if(input.length() == 4) {
			if(input.charAt(1) == '!') {
				if(input.charAt(2) == 'f')
					return("t");
				else
					return("f");
			}
		}
		return("f");
	}
	static boolean checkString(String input, boolean p, boolean q, boolean r) {
		int i;
		boolean correct = true;
		if(input.length() == 5) {
			if(input.charAt(0) == '(') {
				if(input.charAt(1) == 't' || input.charAt(1) == 'f') {
					if(input.charAt(2) == '&' || input.charAt(2) == '|') {
						if(input.charAt(3) == 't' || input.charAt(3) == 'f') {
							if(input.charAt(4) == ')') 
								return(true);
							else
								return(false);
						}
						else
							return(false);
					}
					else
						return(false);
				}
				return(false);
			}
			return(false);
		}
		if(input.length() == 4) {
			if(input.charAt(0) == '(') {
				if(input.charAt(1) == '!') {
					if(input.charAt(2) == 't' || input.charAt(2) == 'f') {
						if(input.charAt(3) == ')') {
							return(true);
						}
						else
							return(false);
					}
					else
						return(false);
				}
				else
					return(false);
			}
			else
				return(false);
		}
		else
			return(false);
	}

	static boolean checkFinalString(String input) {
		if(input.length() != 1)
			return(false);
		else {
			if(input.charAt(0) == 'f' || input.charAt(0) == 't')
				if(input.charAt(0) == 't')
					return(true);
				else
					return(false);
			else
				return(false);
		}
	}
}