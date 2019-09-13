//opgave15_1.java

import tio.*;

class opgave15_1 {
	public static void main(String[] args) {
		int number;
		System.out.println("Geef een number in");
		number = Console.in.readInt();

		multiply(number);
	}

	static void multiply(int number) {
		System.out.println(number * number);
		System.out.println("Geef nog een number in, geef 0 in om te stoppen.");
		number = Console.in.readInt();
		if(number != 0)
			multiply(number);
		else
			return;
	}
}