//opgave16_1.java
//Doel : schrijf de ackerman functie
//input: een getal "m" en een getal "n"
//Strategie: main functie roept ackerman functie op met ack(m, n) en deze gaat recursief verder tot m = 0
//Auteur Berghmans Brent 1334252 1ste Bach Informatica

import tio.*;

class opgave16_1 {
	public static void main(String [] args) {
		int inputM, inputN, total;
		System.out.println("Geef het getal M in");
		inputM = Console.in.readInt();
		System.out.println("Geef het getal N in");
		inputN = Console.in.readInt();

		//Functie oproepen
		total = ack(inputM, inputN);
		System.out.println("De uitkomst is: " + total);
	}

	static int ack(int inputM, int inputN) {
		int total = 0;

		//Stop-case
		if (inputM == 0)
			return(inputN + 1);

		if (inputM > 0 && inputN == 0)
			total += ack(inputM - 1, 1);

		if (inputM > 0 && inputN > 0)
			total += ack(inputM - 1, ack(inputM, inputN - 1));

		return(total);
	}
}