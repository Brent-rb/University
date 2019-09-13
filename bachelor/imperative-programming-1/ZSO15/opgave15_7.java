//opgave15_7.java

import tio.*;

class opgave15_7 {
	public static void main(String[] args) {
		int length, searchNum, place;
		System.out.println("Gimme the length NOAW!");
		length = Console.in.readInt();
		int []table = new int[length];
		table = randomGen(length);
		table = sortTable(table, 0);
		System.out.println("Gimme the search number NOAW!");
		searchNum = Console.in.readInt();
		place = searchBinary(table, 0, length - 1, searchNum);
		writeTable(table);
		if (place >= 0)
			System.out.println("Getal gevonden op plaats " + (place + 1));
		else
			System.out.println("Getal is niet gevonden, sorry");

	}
	static int searchBinary(int[] table, int begin, int end, int searchNum) {
		int middle = (begin + end) / 2;
		int place = -1;
		if(begin <= end) {
			System.out.println("Middle is : " + table[middle] + " search is " + searchNum);
			if (searchNum == table[middle]) {
				place = middle;
				return(place);
			}
			if (searchNum < table[middle])
				place = searchBinary(table, begin, middle - 1, searchNum);
			if (searchNum > table[middle])
				place = searchBinary(table, middle + 1, end, searchNum);
		}
		return(place);
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
			table[i] = (int)((Math.random() * 101));
		}
		return(table);
	}

	static int[] sortTable(int []table, int start) {
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
		return(table);
	}
}