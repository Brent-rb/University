import tio.*;

class opgave17_3 {
	public static void main(String []args) {
		int begin, end, searchNum, amount, place;
		long start, stop, delta;
		int []table;

		System.out.println("Geef het te zoeken nummer");
		searchNum = Console.in.readInt();
		System.out.println("Geef de lengte van de tabel");
		table = new int[Console.in.readInt()];
		table = randomGen(table.length);
		table = sortTable(table, 0);

		start = System.currentTimeMillis();
		amount = searchBinary(table, 0, table.length, searchNum, 0);
		stop = System.currentTimeMillis();
		delta = stop - start;
		System.out.println("Binair zoeken heeft: " + amount + " keer door de string gegaan in: " + delta + "ms");

		start = System.currentTimeMillis();
		amount = searchLinear(table, 0, table.length, searchNum);
		stop = System.currentTimeMillis();
		delta = stop - start;
		System.out.println("Linear zoeken heeft: " + amount + " keer door de string gegaan in: " + delta + "ms");
	}

	static int searchBinary(int[] table, int begin, int end, int searchNum, int amount) {
		int middle = (begin + end) / 2;
		int place = -1;
		if(begin <= end) {
			System.out.println("Middle is : " + table[middle] + " search is " + searchNum);
			if (searchNum == table[middle]) {
				place = middle;
				amount++;
				return(amount);
			}
			if (searchNum < table[middle]) {
				amount += searchBinary(table, begin, middle - 1, searchNum, amount);
				amount++;
			}
			if (searchNum > table[middle]){
				amount += searchBinary(table, middle + 1, end, searchNum, amount);
				amount++;
			}
		}
		return(amount);
	}

	static int[] randomGen(int length) {
		int i;
		int []table = new int[length];
		for(i = 0; i < table.length; i++) {
			table[i] = (int)((Math.random() * 101));
		}
		return(table);
	}

	static int searchLinear(int[] table, int begin, int end, int searchNum) {
		int i;
		for(i = begin; i < end; i++) {
			if(table[i] == searchNum)
				return(i);
		}
		return(i);
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