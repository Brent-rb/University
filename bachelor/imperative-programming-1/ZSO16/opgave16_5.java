//opgave16_5.java

import tio.*;

class opgave16_5_it {
	public static void main(String [] args) {
		String input;
		System.out.println("Geef een string in");
		input = Console.in.readLine();

		if(checkParen(input))
			System.out.println("Hij is juist genest");
		else
			System.out.println("Hij is fout genest");
	}

	static boolean checkParen(String input) {
		int i, amountOpen = 0, amountClosed = 0;
		boolean correct = true;
		for(i = 0; i < input.length() && correct ; i++) {
			if(amountOpen == 0 && amountClosed == 0 || amountOpen > amountClosed) {
				if(input.charAt(i) == '(')
					amountOpen++;
				if(input.charAt(i) == ')')
					amountClosed++;
			}
			else
				correct = false;

		}

		return(correct);
	}
}

class opgave16_5_re {
	public static void main(String [] args) {
		String input;
		System.out.println("Geef een string in");
		input = Console.in.readLine();

		if(checkParen(input))
			System.out.println("Hij is juist genest");
		else
			System.out.println("Hij is fout genest");
	}

	static boolean checkParen(String input) {
		int i, j, amountOpen = 0, amountClosed = 0;
		String newString;
		boolean correct = true;
		if(input.length() >= 2) {
			for(i = input.length() - 1; i >= 0 && input.charAt(i) != '('; i--);
			for(j = i; j < input.length() && input.charAt(j) != ')'; j++);
			newString = input.substring(0, i);
			if(j + 1 < input.length())
				newString += input.substring(j + 1, input.length());
			System.out.println("Newstring is " + newString);
			correct = checkParen(newString);

		}
		else
			if(input.length() == 1)
				return(false);
			if(input.length() == 0)
				return(true);

		return(correct);
	}
}