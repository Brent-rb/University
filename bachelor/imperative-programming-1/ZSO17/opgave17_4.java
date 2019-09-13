import tio.*;
import java.util.*;
/**
*@param n = nigga
*@author Brent Berghmans
*/
class opgave17_4 {
	public static void main(String[] args) {
		int i,j;
		int []table;
		long start, stop, delta;
		System.out.println("Geef de lengte van de tabel");
		table = new int[Console.in.readInt()];
		randomGen(table);

		start = System.currentTimeMillis();
		sortNative(table);
		stop = System.currentTimeMillis();
		delta = stop - start;
		writeTable(table);
		System.out.println("sortNative heeft in " + delta + "ms de tabel gesorteerd");


		randomGen(table);
		//writeTable(table);
		start = System.currentTimeMillis();
		table = sortMerge(table);
		stop = System.currentTimeMillis();
		delta = stop - start;
		writeTable(table);
		System.out.println("sortMerge heeft in " + delta + "ms de tabel gesorteerd");



	}

	static void sortNative(int[] table) {
		int holdNum, lowestNum, lowestPos, i, j;
		for(i = 0; i < table.length ; i++) {
			holdNum = table[i];
			lowestNum = table[i];
			lowestPos = i;
			for(j = i ; j < table.length ; j++) {
				if(table[j] < lowestNum) {
					lowestNum = table[j];
					lowestPos = j;
				}
			}
			table[i] = lowestNum;
			table[lowestPos] = holdNum;
		}
	}
	static void randomGen(int[] table) {
		int i;
		for(i = 0; i < table.length; i++) {
			table[i] = (int)((Math.random() * 100) + 1);
		}
	}

	static int[] sortMerge(int[] table)  {
		int middle = table.length / 2; 
		int []left = new int[middle]; 
		int []right = new int[table.length - middle];
		int []newtable = new int[table.length];
		if(table.length <= 1)
			return(table);
		else {
			middle = table.length / 2;
			left = sortMerge(subTable(table, 0, middle));
			//left = sortMerge(Arrays.copyOfRange(table, 0, middle));
			//System.out.println("Left is ");
			//writeTable(left);
			right = sortMerge(subTable(table, middle, table.length));
			//right = sortMerge(Arrays.copyOfRange(table, middle, table.length));
			//System.out.println("Right is ");
			//writeTable(right);
			//System.out.println("Merge is ");
			//writeTable(merge(left,right));
			return(merge(left,right));
		}
	}

	static int[] merge(int[] left, int[] right) {
		int length = left.length + right.length, counterLeft = 0, counterRight = 0;
		int[] table = new int[length];
		int i, j;
		for(i = 0; i < table.length; i++) {
			if(counterLeft < left.length && counterRight < right.length && left[counterLeft] <= right[counterRight]) {
				table[i] = left[counterLeft];
				counterLeft++;
				continue;
			}
			
			if(counterLeft == left.length && counterRight < right.length) {
				table[i] = right[counterRight];
				counterRight++;
				continue;
			}
			
			if(counterLeft < left.length && counterRight < right.length && right[counterRight] < left[counterLeft]) {
				table[i] = right[counterRight];
				counterRight++;
				continue;
			}
			if(counterRight == right.length && counterLeft < left.length) {
				table[i] = left[counterLeft];
				counterLeft++;
				continue;
			}
		}
		return(table);
	}

	static int [] subTable(int[] table, int begin, int end) {
		int i;
		int []newTable = new int[end - begin];

		for(i = 0; i < newTable.length && i + begin < end; i++) {
			newTable[i] = table[begin + i];
		}

		return(newTable);
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
}