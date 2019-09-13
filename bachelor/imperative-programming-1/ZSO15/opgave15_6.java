//opgave15_6.java
import tio.*;

class opgave15_6_it {
	public static void main(String[] args) {
		int length, i, holdNum, lowestNum, lowestPos, j;
		System.out.println("Gimme the length!");
		length = Console.in.readInt();
		int []toSort = new int [length];
		toSort = randomGen(length);
		writeTable(toSort);
		
		for(i = 0; i < toSort.length ; i++) {
			holdNum = toSort[i];
			lowestNum = toSort[i];
			lowestPos = i;
			for(j = i ; j < toSort.length ; j++) {
				if(toSort[j] < lowestNum) {
					lowestNum = toSort[j];
					lowestPos = j;
				}
			}
			toSort[i] = lowestNum;
			toSort[lowestPos] = holdNum;
		}
		writeTable(toSort);
	}

	static void writeTable(int []table) {
		int i, j;
		String spaceGen = "";
		for(i = 0; i < table.length; i++) {
			spaceGen = "" + table[i];
			if (i == 0){
				for(j = 0; j < table.length; j++) {
					System.out.print(" _____");
				}
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j != table.length - 1)
						System.out.print("|     ");
					else
						System.out.println("|     |");
				}
			}
			if(i == 0){
				if(spaceGen.length() == 1)
					System.out.print("|  " + table[i] + "  |");
				if(spaceGen.length() == 2)
					System.out.print("|  " + table[i] + " |");
				if(spaceGen.length() == 3)
					System.out.print("| " + table[i] + " |");
				if(spaceGen.length() == 4)
					System.out.print("| " + table[i] + "|");
				if(spaceGen.length() == 5)
					System.out.print("|" + table[i] + "|");
			}
			else {
				if(spaceGen.length() == 1)
					System.out.print("  " + table[i] + "  |");
				if(spaceGen.length() == 2)
					System.out.print("  " + table[i] + " |");
				if(spaceGen.length() == 3)
					System.out.print(" " + table[i] + " |");
				if(spaceGen.length() == 4)
					System.out.print(" " + table[i] + "|");
				if(spaceGen.length() == 5)
					System.out.print("" + table[i] + "|");
			}
			if (i == table.length - 1) {
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j == 0)
						System.out.print("|_____|");
					else
						System.out.print("_____|");
				}
				System.out.println("\n");
			}
		}
	}

	static int[] randomGen(int length) {
		int i;
		int []table = new int[length];
		for(i = 0; i < table.length; i++) {
			table[i] = (int)((Math.random() * 201) - 100);
		}
		return(table);
	}
}

class opgave15_6_re {
	public static void main(String[] args) {
		int length, i, holdNum, lowestNum, lowestPos, j;
		System.out.println("Gimme the length!");
		length = Console.in.readInt();
		int []toSort = new int [length];
		toSort = randomGen(length);
		writeTable(toSort);
		sortTable(toSort, 0);
		writeTable(toSort);
	}

	static void writeTable(int []table) {
		int i, j;
		String spaceGen = "";
		for(i = 0; i < table.length; i++) {
			spaceGen = "" + table[i];
			if (i == 0){
				for(j = 0; j < table.length; j++) {
					System.out.print(" _____");
				}
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j != table.length - 1)
						System.out.print("|     ");
					else
						System.out.println("|     |");
				}
			}
			if(i == 0){
				if(spaceGen.length() == 1)
					System.out.print("|  " + table[i] + "  |");
				if(spaceGen.length() == 2)
					System.out.print("|  " + table[i] + " |");
				if(spaceGen.length() == 3)
					System.out.print("| " + table[i] + " |");
				if(spaceGen.length() == 4)
					System.out.print("| " + table[i] + "|");
				if(spaceGen.length() == 5)
					System.out.print("|" + table[i] + "|");
			}
			else {
				if(spaceGen.length() == 1)
					System.out.print("  " + table[i] + "  |");
				if(spaceGen.length() == 2)
					System.out.print("  " + table[i] + " |");
				if(spaceGen.length() == 3)
					System.out.print(" " + table[i] + " |");
				if(spaceGen.length() == 4)
					System.out.print(" " + table[i] + "|");
				if(spaceGen.length() == 5)
					System.out.print("" + table[i] + "|");
			}
			if (i == table.length - 1) {
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j == 0)
						System.out.print("|_____|");
					else
						System.out.print("_____|");
				}
				System.out.println("\n");
			}
		}
	}

	static int[] randomGen(int length) {
		int i;
		int []table = new int[length];
		for(i = 0; i < table.length; i++) {
			table[i] = (int)((Math.random() * 201) - 100);
		}
		return(table);
	}

	static void sortTable(int []table, int start) {
		int i, lowestNum, tempNum, lowestPos;
		if(start < table.length) {
			lowestNum = table[start];
			lowestPos = start;
			tempNum = table[start];
			for(i = start; i < table.length; i++) {
				if (table[i] < lowestNum) {
					lowestNum = table[i];
					lowestPos = i;
				}
			}
			table[start] = lowestNum;
			table[lowestPos] = tempNum;
			sortTable(table, start + 1);
		}
		else
			return;
		return;
	}
}