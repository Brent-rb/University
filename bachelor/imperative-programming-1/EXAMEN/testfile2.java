//testfile2.java

//mergesort testfile
import tio.*;

class mergesort {
	public static void main(String [] args) {
		int [] table = new int[Integer.parseInt(args[0])];
		genTable(table);
		//writeTable(table);
		table = mergeSort(table);
		writeTable(table);
	}

	public static void genTable(int [] table) {

		for(int i = 0; i < table.length; i++) {
			table[i] = (int)((Math.random() * 100) - 50);
		}

	}

	public static void writeTable(int [] table){
		for(int i = 0; i < table.length; i++) {
			if(i == 0)
				System.out.print("| " + table[i] + " |");
			else
				System.out.print(" " + table[i] + " |");
		}
		System.out.println("\n");
	}

	public static int[] mergeSort(int [] table) {
		int middle = table.length / 2;
		int []left;
		int []right;

		if(table.length == 1)
			return(table);

		left = subTable(table, 0, middle);
		right = subTable(table, middle, table.length);
		left = mergeSort(left);
		right = mergeSort(right);

		return(merge(left, right));

	}

	public static int[] subTable(int [] table, int begin, int end) {
		int i;
		int []newTable = new int [end - begin];

		for(i = 0; i < newTable.length; i++) {
			newTable[i] = table[begin + i];
		}

		return(newTable);
	}

	public static int[] merge(int [] left, int [] right) {
		int [] newTable = new int [left.length + right.length];
		int counterLeft = 0, counterRight = 0, i;

		for(i = 0; i < newTable.length ; i++) {
			if(counterLeft < left.length && counterRight < right.length) {
				if(left[counterLeft] > right[counterRight]){
					newTable[i] = left[counterLeft];
					counterLeft++;
				}
				else {
					newTable[i] = right[counterRight];
					counterRight++;
				}
			}
			else if(counterLeft < left.length) {
				newTable[i] = left[counterLeft];
				counterLeft++;
			}
			else {
				newTable[i] = right[counterRight];
				counterRight++;
			}
		}

		return(newTable);
	}
}