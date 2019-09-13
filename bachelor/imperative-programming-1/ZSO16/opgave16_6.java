//opgave16_6.java

import tio.*;

class opgave16_6_binair {
	public static void main(String[] args) {
		int lengthTable = 1000, toSearchNum = 20;
		//lengthTable = Console.in.readInt();
		//toSearchNum = Console.in.readInt();
		int []table = new int[lengthTable];
		table = randomGen(lengthTable);
		table = sortTable(table, 0);
		System.out.println("Aantal stappen: " + searchBinary(table, 0, table.length - 1, toSearchNum, 1));

	}

	static int searchBinary(int[] table, int begin, int end, int searchNum, int steps) {
		int middle = (begin + end) / 2;
		int place = -1;
		if(begin <= end) {
			if (searchNum == table[middle]) {
				return(steps);
			}
			if (searchNum < table[middle])
				steps = searchBinary(table, begin, middle - 1, searchNum, steps + 1);
			if (searchNum > table[middle])
				steps = searchBinary(table, middle + 1, end, searchNum, steps + 1);
		}
		return(steps);
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

class opgave16_6_linear {
	public static void main(String[] args) {
		int lengthTable = 1000, toSearchNum = 20;
		//lengthTable = Console.in.readInt();
		//toSearchNum = Console.in.readInt();
		int []table = new int[lengthTable];
		table = randomGen(lengthTable);
		table = sortTable(table, 0);
		System.out.println("Aantal stappen nodig: " + searchLinear(table, 0, table.length, toSearchNum, 1));

	}

	static int searchLinear(int[] table, int begin, int end, int searchNum, int steps) {
		int i;

		for(i = begin; i < end; i++, steps++) {
			if(searchNum == table[i])
				return(steps);
		} 
		return(steps);
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