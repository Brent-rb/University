//opgave16_4.java

 //Doel n = lengte , m = aantal waar  100 010 001 
 //Auteur : Brent Berghmans

import tio.*;

class opgave16_4_re {
	public static void main(String [] args) {
		int inputLength, inputAmount;
		System.out.println("Geef N");
		inputLength = Console.in.readInt();
		System.out.println("Geef M");
		inputAmount = Console.in.readInt();

		bits(inputLength, inputAmount, 0, "");
	}

	static void bits(int inputLength, int inputAmount, int sumPrev, String answer) {
		int i;
		if(inputLength == 0){
			System.out.println(answer);
			return;
		}
		if(sumPrev + inputLength <= inputAmount)
			bits(inputLength - 1, inputAmount, sumPrev + 1, answer + "1");
		else {
			if(sumPrev < inputAmount) {
				bits(inputLength - 1, inputAmount, sumPrev + 1, answer + "1");
				bits(inputLength - 1, inputAmount, sumPrev, answer + "0");
			}
			else
				bits(inputLength - 1, inputAmount, sumPrev, answer + "0");
		}
		return;
	}
}

class opgave16_4_it {
	public static void main(String [] args) {
		int inputLength, inputAmount, i, maxNum, minNum = 0, test;
		String output;
		System.out.println("Geef N");
		inputLength = Console.in.readInt();
		System.out.println("Geef M");
		inputAmount = Console.in.readInt();

		maxNum = (int)(Math.pow(2,inputLength) - 1);

		for(i = 1; i <= inputAmount; i++) {
			minNum += (int)(Math.pow(2,i - 1));
		}

		for(i = minNum; i  < maxNum; i++) {
			output = toBin(i, inputLength);
			test = sumBin(output);
			if (test == inputAmount)
				System.out.println(output);
		}
	}

	static int sumBin(String input) {
		int i, sum = 0;
		for (i = 0; i < input.length(); i++) {
			if (input.charAt(i) == '1')
				sum++;
		}
		return(sum);
	}

	static String toBin(int input, int length) {
		int i = 0;
		String binString = "";
		while (input / 2 != 0) {
			binString = "" + (input % 2) + binString;
			input /= 2;
			i++;
		}
		binString = "" + (input % 2) + binString;
		input /= 2;
		i++;
		if(i != length)
			while(i != length) {
				binString = "0" + binString;
				i++;
			}
		return(binString);
	}
}