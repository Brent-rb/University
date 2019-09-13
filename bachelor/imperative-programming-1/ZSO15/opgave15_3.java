//opgave15_3.java
//Auteur: Brent Berghmans
//Doel Equivalent recursief programma maken.

import tio.*;

class opgave15_3_it {
	public static void main(String[] args) {
		long input;
		System.out.println("Gimme something");
		input = Console.in.readInt();
		System.out.println(f(input));
	}

	static long f(long n) {

		int sum = 0;

		while (n > 0) {
			System.out.println("adding 2x" + n);
			sum += 2 * n;
			n--;
		}

		return(sum);
	}
}

class opgave15_3_re {
	public static void main(String[] args) {
		long input;
		System.out.println("Gimme something");
		input = Console.in.readInt();
		System.out.println(f(input));
	}

	static long f(long input) {
		int sum = 0;

		if(input == 0)
			return(0);
		else {
			System.out.println("adding 2x" + input);
			sum += (2 * input) + f(input - 1);
		}
		return(sum);
	}
}

//Als we een hele grote waarde ingeven dan crasht de recursieve versie omdat we zonder geheugen zitten voor al die functie open te houden.