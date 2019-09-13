import tio.*;

class opgave14_13_recursief {
	public static void main(String[] args) {
		int i = 0, stairs, steps, stepsBackward, amountOfSteps = 2;
		System.out.println("Geef x");
		stairs = Console.in.readInt();
		System.out.println("Geef y");
		steps = Console.in.readInt();
		System.out.println("Geef z");
		stepsBackward = Console.in.readInt();

		amountOfSteps = countSteps(stairs, steps, stepsBackward, i,  0);

		System.out.println("Je moet " + amountOfSteps + " treden stappen met deze parameters.");

	}

	static int countSteps(int x, int y, int z, int i, int amountOfSteps) {
		int total = 0;
		amountOfSteps = 2;
		if(i < x)
			total = amountOfSteps + countSteps(x, y , z, i + y - z, amountOfSteps);
		if(i == x)
			return(0);
		return(total - 1);
	}
}

class opgave14_13_iteratief {
	public static void main(String[] args) {
		int i = 0, stairs, steps, stepsBackward, amountOfSteps;
		System.out.println("Geef x");
		stairs = Console.in.readInt();
		System.out.println("Geef y");
		steps = Console.in.readInt();
		System.out.println("Geef z");
		stepsBackward = Console.in.readInt();

		for(amountOfSteps = 0; stairs > 0; ) {
			stairs += stepsBackward;
			amountOfSteps++;
			if(stairs <= 0)
				break;
			stairs -= steps;
			amountOfSteps++; 
			if(stairs <= 0)
				break;
		}

		System.out.println("Je moet " + amountOfSteps + " treden stappen met deze parameters.");
	}
}