//opgave15_2.java

import tio.*;

class opgave15_2 {
	public static void main(String[] args) {
		int number = 1;

		multiply(number);
	}

	static void multiply(int number) {
		
		System.out.println("Geef een number in, geef 0 in om te stoppen.");
		number = Console.in.readInt();
		if(number != 0){
			multiply(number);
			System.out.println(number * number);
		}
		else
			return;
	}
}