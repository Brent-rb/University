import tio.*;

class brewery {
	static int [] beer;
	static String [] status;
	static int stiemerbeek = 0;
	public static void main(String [] args) {
		askInput();
		calcStatus();
		System.out.println();
		System.out.println("Begintoestand:");
		printLiters();
		System.out.println();
		printStatus();
		System.out.println();
		calcBeer();
		System.out.println("In totaal " + stiemerbeek + " liter bier in de Stiemerbeek geloosd.");
	}


	static void askInput() {
		int tempNum, i;

		do {
			System.out.println("Hoeveel koten?");
			tempNum = Console.in.readInt();
		} while(tempNum <= 0);

		beer = new int [tempNum];
		status = new String [tempNum];

		for(i = 0; i < beer.length; i++) {
			do {
				System.out.println("Geef inhoud vat " + (i + 1) + ":");
				tempNum = Console.in.readInt();
			} while(tempNum < 0);

			beer[i] = tempNum;
		}
	}

	static void printLiters() {
		int i;

		for(i = 0; i < beer.length; i++) {
			if(i == 0)
				System.out.print("" + beer[i]);
			else
				System.out.print(" " + beer[i]);
		}
	}

	static void calcStatus() {
		int i, tempNum;

		for (i = 0; i < beer.length; i++) {
			tempNum = beer[i];
			if(tempNum >= 90)
				status[i] = "Rood";
			else if(tempNum >= 80)
				status[i] = "Oranje";
			else
				status[i] = "Groen";
		}
	}

	static void printStatus() {
		int i;

		for(i = 0; i < status.length; i++) {
			System.out.println("Vat " + (i + 1) + ": " + status[i]);
		}
	}

	static void calcBeer() {
		int i, fase = 1;
		boolean notFinished = checkFinished();

		while(notFinished) {
			System.out.println("Fase " + fase);
			System.out.println("---------");

			for(i = 0; i < beer.length; i++) {
				calcNext(i);
			}

			printLiters();
			System.out.println();
			System.out.println();

			printStatus();
			System.out.println();

			notFinished = checkFinished();
			fase++;
		}
	}

	static void calcNext(int pos) {
		int i, difference = 0, differenceMax;

		if(pos == (beer.length - 1)) {
			printLiters();
			if(status[pos].equals("Rood") || status[pos].equals("Oranje")) {
				difference = (beer[pos] - 79);
				beer[pos] -= difference;
				stiemerbeek += difference;
			}
			System.out.println(" " + (pos + 1) + " -> Stiemerbeek: " + difference + " liter");
			calcStatus();
			return;
		}
		else {
			if(status[pos].equals("Groen")) {
				if(status[pos + 1].equals("Rood")) {
					difference = beer[pos + 1] - 79;
					differenceMax = 79 - beer[pos];
					if(difference > differenceMax)
						difference = (differenceMax * -1);
					else
						difference *= -1;
				}
			}
			else if(status[pos].equals("Oranje")) {
				if(status[pos + 1].equals("Groen") || status[pos + 1].equals("Oranje")) 
					difference = 10;
			}
			else if(status[pos].equals("Rood")) {
				if(status[pos + 1].equals("Groen")) {
					difference = beer[pos] - 79;
					differenceMax = 89 - beer[pos + 1];
					if(difference > differenceMax)
						difference = differenceMax;
				}
				else if(status[pos + 1].equals("Oranje"))
					difference = 5;
			}
		}
		printLiters();
		beer[pos] -= difference;
		beer[pos + 1] += difference;
		System.out.println(" " + (pos + 1) + " -> " + (pos + 2) + ": " + difference + " liter");
		calcStatus();
	}

	static boolean checkFinished() {
		int i;
		boolean finished = true;

		for(i = 0; i < status.length && finished; i++) {
			if(!(status[i].equals("Groen")))
				finished = false;
		}
		return(!finished);
	}
}