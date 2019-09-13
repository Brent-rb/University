//Taak 15
//Doel R&A Exp checken
//Auteur: Brent Berghmans 1334252

import tio.*;

class taak15_1 {
	public static void main(String[] args) {
		//Variabelen declareren
		String input, tempString = "";
		int amountOfItems, i, j,k;
		char tempChar;
		boolean correct = true, output;

		String []inputTable = {"x", "1", "30000", "(x+1)", "(x+x)", "(((3*1)+(4/3))-2)", "(O-1)", "", "()",")","+","(+)", "(+", "(3+", "x+1", "(1+y)", "(-1)", "(1+2+3)", "jelle-jonny"};
		boolean []outputTable = {true,true,true,true,true,true,true,false,false,false,false,false,false,false,false,false,false,false,false};

		for(k = 0; k < inputTable.length ; k++){
			correct = true;
			tempString = "";
			input = inputTable[k];
			output = outputTable[k];
		/*
		//Input controle
		//if(args.length < 1)
		//	return;
		//else
		//	input = args[0];

		//Aantal items in een string bepalen
		if(input.length() == 0) {

			correct = false;
			System.out.println("Input: " + input + ", expected output was: " + output + ", out was: " + correct);
			continue;
		}
		
		while(input.length() > 1 && correct) {
			if(checkOperators(input) == '0' && checkThing(input) == '0')
				if(checkItems(input) == 1){
					correct = true;
					input = "";
				}
				else  {
					correct = false;
					continue;
				}
			else if (checkThing(input) == '1'){
				correct = false;
				continue;
			}
			for(i = input.length() - 1; i >= 0 && input.charAt(i) != '(' ; i--) {
			}
			if(i < 0 && checkItems(input) != 1){
				correct = false;
				continue;
			}
			if(i < 0 && checkItems(input) == 1 && checkOperators(input) == 0 && checkThing(input) == 0){
				correct = true;
				input = "";
				System.out.println("Input: " + inputTable[k] + ", expected output was: " + output + ", out was: " + correct);
				continue;

			}
			for(j = i; j < input.length() && input.charAt(j) != ')'; j++) {
			}
			if(j + 1 <= input.length()){
				tempString = input.substring(i, j + 1);
			}
			else if(checkItems(input) == 1 && checkOperators(input) == 0)
				correct = false;
			
			if(checkString(tempString)) {
				tempString = input.substring(0,i) + "x" + input.substring(j + 1, input.length());
				
				input = tempString;
			}
			else
				correct = false;
		}

			System.out.println("Input: " + inputTable[k] + ", expected output was: " + output + ", out was: " + correct);
		*/
		correct = checkString(input);
		System.out.println("Input: " + inputTable[k] + ", expected output was: " + output + ", out was: " + correct);
		}
	}

	//Functie die het aantal items in een string bepaalt
	static int checkItems(String input) {
		int i, amountOfItems = 0;
		char tempChar;

		//Check het items in een string 
		for(i = 0; i < input.length(); i++) {
			tempChar = input.charAt(i);
			if(tempChar == 'x' || tempChar >= '0' && tempChar <= '9') {
				while(i < input.length() && (tempChar == 'x' || tempChar >= '0' && tempChar <= '9')) {
					tempChar = input.charAt(i);
					i++;
					
				}
				amountOfItems++;
			}
		}

		return(amountOfItems);
	}

	static int checkThing(String input) {
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
		String tempString;
		int i,j, bracketsAmount = 0;
		Boolean correct = true;
		if(input.length() == 0)
			return(false);
		if(input.charAt(0) == '(') {
			if(input.charAt(1) >= '0' && input.charAt(1) <= '9') {
				for(i = 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
				if(input.charAt(i) == '*' || input.charAt(i) == '-' || input.charAt(i) == '/' || input.charAt(i) == '+') {
					if(input.charAt(i + 1) >= '0' && input.charAt(i + 1) <= '9') {
						for(i = i + 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
						if(input.charAt(i) == ')')
							correct = true;
						else
							correct = false;
					}
					else {
						if(input.charAt(i + 1) == 'x') {
							if(input.charAt(i + 2) == ')') {
								correct = true;
							}
							else {
								correct = false;
							}
						}
						else {
							correct = false;
						}
						if(input.charAt(1) == '(') {
							bracketsAmount = 1;
							for(j = i + 1; j < input.length() && bracketsAmount != 0; j++) {
								if(input.charAt(j) == '(')
									bracketsAmount++;
								if(input.charAt(j) == ')')
								bracketsAmount--;
							}
							tempString = input.substring(i + 1, j);
							if(checkString(tempString)) {
								input = input.substring(0,i + 1) + "x" + input.substring(j + 1);
								if(checkString(input))
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
				}
				else
					correct = false;
			}
			else {
				if(input.charAt(1) == 'x'){
					if(input.charAt(2) == '*' || input.charAt(2) == '-' || input.charAt(2) == '/' || input.charAt(2) == '+') {
						if(input.charAt(3) >= '0' && input.charAt(3) <= '9') {
							for(i = 3; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
							if(input.charAt(i) == ')')
								correct = true;
							else
								correct = false;
						}
						else {
							if(input.charAt(3) == 'x'){
								if(input.charAt(4) == ')'){
									correct = true;
								}
								else{
									correct = false;
								}
							}
							if(input.charAt(3) == '(') {
								bracketsAmount++;
								for(i = 3; i < input.length() && bracketsAmount != 0; i++) {
									if(input.charAt(i) == '(')
										bracketsAmount++;
									if(input.charAt(i) == ')')
										bracketsAmount--;
								}
								tempString = input.substring(3, i);
								if(checkString(tempString)) {
									input = input.substring(0,3) + "x" + input.substring(i + 1);
									if(checkString(input))
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
					}
					else
						correct = false;
				}
				if(input.charAt(1) == '(') {
					bracketsAmount++;
					for(i = 1; i < input.length() && bracketsAmount != 0; i++) {
						if(input.charAt(i) == '(')
							bracketsAmount++;
						if(input.charAt(i) == ')')
							bracketsAmount--;
					}
					tempString = input.substring(1, i);
					if(checkString(tempString)) {
						input = input.substring(0,1) + "x" + input.substring(i + 1);
						if(checkString(input))
							correct = true;
						else
							correct = false;
					}
					else correct = false;
				}
				else
					correct = false;
			}
			
		}
		else 
			if(checkOperators(input) == 0 && checkItems(input) == 1 && checkThing(input) == 0)
				correct = true;
			else
				correct = false;
		return(correct);
	}
}