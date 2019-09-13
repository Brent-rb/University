//checkparen.java

class checkparen {
	static boolean isValid;
	public static void main(String[] args) {
		String input = args[0], substring;
		isValid = true;
		int i, j, amountOfNumbers;
		int[] table = new int [args.length - 1];
		for(i = 1; i < args.length; i++) {
			table[i - 1] = Integer.parseInt(args[i]);
		}
		System.out.println("Input is: " + input);
		amountOfNumbers = checkNumbers(input);
		input = replace(input, table);

		while(checkBrackets(input) != 0) {
			for(i = 0; i < input.length() && input.charAt(i) != ')'; i++);
			if(i == input.length())
				i--;
			for(j = i - 1; j >= 0 && input.charAt(j) != '('; j--);
			if(j == -1)
				j++;
			substring = input.substring(j, i + 1);
			if(checkNumbers(substring) == 2 && checkValid(substring))
				substring = calcSubstring(substring);
			else
				substring = priority(substring.substring(1, substring.length() - 1));
			input = input.substring(0, j) + substring + input.substring(i + 1);

		}
		if(!(checkNumbers(input) == 1))
			input = priority(input);
		if(isValid)
			System.out.println("Output is: " + input);
		else
			System.out.println("Foutieve String");

	}
	static String replace(String input, int[] table) {
		int i,j,k, number;

		for(i = 0; i < input.length(); i++) {
			if(input.charAt(i) == '$') {
				for(k = i + 1; i < input.length() && input.charAt(k) >= '0' && input.charAt(k) <= '9'; k++);
				number = toNumb(input.substring(i + 1, k));
				input = input.substring(0, i) + table[number - 1] + input.substring(k);
			}
		}
		return(input);
	}

	static int checkNumbers(String input) {
		int i, j, amountOfNumbers = 0;

		for(i = 0; i < input.length(); i++) {
			if(input.charAt(i) >= '0' && input.charAt(i) <= '9') {
				amountOfNumbers++;
				for(i = i; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++) {
				}
			}
		}
		return(amountOfNumbers);
	}
	static boolean checkValid(String input) {
		int i = 0;
		if(input.length() == 0)
			return(true);

		boolean isValid = true;
		if(input.charAt(0) != '(' || input.charAt(input.length() - 1) != ')')
			isValid = false;
		if(isValid && (input.charAt(1) < '0' || input.charAt(1) > '9'))
			isValid = false;
		else if(isValid) {
			for(i = 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
			if(i > input.length() - 1)
				isValid = false;
			if(isValid && input.charAt(i) != '+' && input.charAt(i) != '-' && input.charAt(i) != '*' && input.charAt(i) != '/') {
				isValid = false;
			}
			else if(isValid && (input.charAt(i + 1) < '0' || input.charAt(i + 1) > '9'))
				isValid = false;
			else if(isValid) {
				for(i = i + 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
				if(i != (input.length() - 1) || input.charAt(i) != ')')
					isValid = false;
			}
		}

		return(isValid);
	}

	static String calcSubstring(String input) {
		int i, left, right, output = 0;
		char c;
		if(input.length() == 0)
			return("");
		for(i = 1; i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i++);
		c = input.charAt(i);
		left = toNumb(input.substring(1, i));
		right = toNumb(input.substring(i + 1, input.length() - 1));
		if(c == '+')
			output = left + right;
		if(c == '-')
			output = left - right;
		if(c == '*')
			output = left * right;
		if(c == '/')
			output = left / right;

		return("" + output);
	}

	static int toNumb(String input) {
		int i, j;
		int number, total = 0;

		for(i = 0; i < input.length() ; i++) {
			number = input.charAt(i) - '0';
			for(j = 1; j < input.length() - i; j++)
				number *= 10;
			total += number;
		}

		return(total);
	}

	static String priority(String input) {
		if(input.length() == 0) {
			isValid = false;
			return("");
		}
		int i,j,k, amountOfNumbers = checkNumbers(input);
		char c, highestChar;
		boolean isValid;
		boolean []table;
		//System.out.println("Input is :" + input);
		while(amountOfNumbers != 1) {
			table = new boolean[input.length()];
			highestChar = checkHighestChar(input);
			for(i = 0; i < table.length; i++) {
				if(highestChar == '*') {
					if(input.charAt(i) == '*' || input.charAt(i) == '/') {
						for(j = i - 1; j >= 0 && input.charAt(j) >= '0' && input.charAt(j) <= '9'; j--);
						for(k = i + 1; k < input.length() && input.charAt(k) >= '0' && input.charAt(k) <= '9'; k++);
						if(!(j >= 0 && k < input.length()) || input.charAt(j) != '(' && input.charAt(k) != ')') {
							table[i] = true;
						} 
					}
				}
				else if(highestChar == '-') {
					if(input.charAt(i) == '-' || input.charAt(i) == '+') {
						for(j = i - 1; j >= 0 && input.charAt(j) >= '0' && input.charAt(j) <= '9'; j--);
						for(k = i + 1; k < input.length() && input.charAt(k) >= '0' && input.charAt(k) <= '9'; k++);
						if(!(j >= 0 && k < input.length()) || input.charAt(j) != '(' && input.charAt(k) != ')') {
							table[i] = true;
						} 
					}
				}
			}
			for(i = 0; i < table.length && !table[i]; i++);
			//System.out.println("i is: " + i + table[i]);
			for(j = i + 1; j < input.length() && input.charAt(j) >= '0' && input.charAt(j) <= '9'; j++);
			for(i = i - 1; i >= 0 && input.charAt(i) >= '0' && input.charAt(i) <= '9'; i--);
			if(i >= 0 && input.charAt(i) == ')') {
				for(i = i; i >= 0 && input.charAt(i) != '(';i--);
			}
			if(j < input.length() && input.charAt(j) == '(') {
				for(j = j; j < input.length() && input.charAt(j) != ')'; j++);
			}

			isValid = checkValid("(" + input.substring(i +1, j) + ")");
			input = input.substring(0, i + 1) + calcSubstring("(" + input.substring(i + 1, j) + ")") + input.substring(j);

			//System.out.println("Input is :" + input);
			amountOfNumbers = checkNumbers(input);
		}
		return(input);
	}

	static int checkOperators(String input) {
		int operators = 0;
		int i;
		char c;
		for(i = 0; i < input.length(); i++) {
			c = input.charAt(i);
			if(c == '*' || c == '/' || c == '-' || c == '+')
				operators++;
		}
		return(operators);
	}

	static int checkBrackets(String input) {
		int brackets = 0;
		int i;
		char c;
		for(i = 0; i < input.length(); i++) {
			c = input.charAt(i);
			if(c == '(' || c == ')')
				brackets++;
		}
		return(brackets);
	}

	static char checkHighestChar(String input) {
		int i, j,k;
		char highestChar = '-', c;
		for(i = 0; i < input.length(); i++) {
			if(input.charAt(i) == '*' || input.charAt(i) == '/') {
				for(j = i - 1; j >= 0 && input.charAt(j) >= '0' && input.charAt(j) <= '9'; j--);
				for(k = i + 1; k < input.length() && input.charAt(k) >= '0' && input.charAt(k) <= '9'; k++);
				if(!(j >= 0 && k < input.length()) || input.charAt(j) != '(' && input.charAt(k) != ')') {
					highestChar = '*';
					return(highestChar);
				} 
			}
		}
		return(highestChar);
	}	
}