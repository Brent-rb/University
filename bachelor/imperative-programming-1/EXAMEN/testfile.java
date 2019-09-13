class vraag6 {
	public static void main(String [] args) {
		int i, row, column, length;
		double [][] table = new double [5][4];
		double []table1;
		double []table2;
		int amountDifferent = 1;
		double prevNum;

		//Random table genereren (Enkel om te testen)
		for(row = 0; row < table.length; row++) {
			for(column = 0; column < table[row].length; column++) {
				table[row][column] = (double)(((int)((Math.random() * 2000)) / 100.0)- 100.0);
				System.out.print("" + table[row][column] + "  ");
			}
			System.out.println();
		}
		System.out.println();
		//

		//Tabel naar een rij omzetten --> voor mergesort
		table1 = toOneD(table);
		//Tabel sorteren met mergeSort
		table1 = mergeSort(table1);
		//Initialiseren van prevNum
		prevNum = table1[0];
		//Tellen hoeveel verschillende nummers er in zitten
		for(i = 1; i < table1.length; i++) {
			if(table1[i] != prevNum) {
				prevNum = table1[i];
				amountDifferent++;
			}
		}
		//Nieuwe tabel aanmaken met het aantal
		table2 = new double[amountDifferent];
		//Reset van prevNum
		prevNum = table1[0];
		//Reset van aantal verschillende nummers
		amountDifferent = 1;
		//Dit moet omdat we table1[0] als basis geval nemen
		table2[0] = prevNum;
		for(i = 1; i < table1.length; i++) {
			//Als we een getal verschillend van het vorig getal tegenkomen --> in de tabel schrijven
			if(table1[i] != prevNum) {
				table2[amountDifferent] = table1[i];
				prevNum = table1[i];
				amountDifferent++;
			}
		}

		//De gesorteerde tabel afprinten (visuele controle)
		for(i = 0; i < table2.length; i++) {
			System.out.print("" + table2[i] + "  ");
		}
		System.out.println();
		System.out.println();
		System.out.println();
		//

		//I moet hier k voorstellen, enkel voor te testen, anders loop weglaten en i door k vervangen
		for(i = 0; i <= 15; i++) {
			if(((table2.length - 1) - i) >= 0) {
				System.out.println("Het op " + i + " na kleinste getal is: " + table2[((table2.length - 1) - i)]);
			}
			else 
				System.out.println("Het op " + i + " na kleinste getal is: " + table2[0]);
		}

	}

	public static double[] toOneD(double[][] table2d) {
		int i, row, column, length = table2d.length * table2d[0].length;
		double []table1d = new double[length];

		for(row = 0, i = 0; row < table2d.length; row++) {
			for(column = 0; column < table2d[row].length; column++, i++) {
				table1d[i] = table2d[row][column];
			}
		}

		return(table1d);
	}

	static double[] mergeSort(double[] table) {
		int middle = table.length / 2;
		double []left;
		double []right;

		if(table.length < 2)
			return(table);

		left = mergeSort(subtable(table, 0, middle));
		right = mergeSort(subtable(table, middle, table.length));
		return(merge(left, right));
	}

	static double[] subtable(double[] table, int begin, int end) {
		double [] newTable = new double[end - begin];
		int i;

		for(i = 0; i < newTable.length; i++) {
			newTable[i] = table[begin + i];
		}

		return(newTable);
	}

	static double[] merge(double[] left, double[] right) {
		double[] newTable = new double[left.length + right.length];
		int counterLeft = 0, counterRight = 0, i = 0;
		for(i = 0; i < newTable.length; i++) {
			if(counterLeft < left.length && counterRight < right.length) {
				if(left[counterLeft] <= right[counterRight]) {
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