/***************************\
|****** 2DIMENSIONAL *******|
\***************************/


	static void writeTable (int [][]table) {
		int n1 = table.length;
		int n2 = table[0].length;
		int row, colomn, i = 0;
		for (row = 0; row < n1; row++) {
			for(i = 0; i < n2; i++) {
				if(row == 0) {
					if (i < n2)
						System.out.print(" _____");
					if (i == n2-1) {
						System.out.println();
					}
				}
			}
			for (i = 0; i < n2; i++) {
				if (i == 0)
					System.out.print("|     |");
				else
					System.out.print("     |");
			}
			System.out.println();
			for (colomn = 0; colomn < n2; colomn++) {
				if (table[row][colomn]) {
					amountStars++;
					if(colomn != n2-1)
						System.out.print("|  Q  ");
					else
						System.out.println("|  Q  |");
				}
				else {
					if(colomn != n2-1)
						System.out.print("|     ");
					else
						System.out.println("|     |");
				}
			}
			for (i = 0; i < n2; i++) {
				if(i == 0)
					System.out.print("|_____|");
				else
					System.out.print("_____|");
			}
			System.out.println();
		}
	}

/***************************\
|****** 1DIMENSIONAL *******|
\***************************/


	static void writeTable(int []table) {
		int i, j;

		for(i = 0; i < table.length; i++) {
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
			if(i == 0)
				System.out.print("|  " + table[i] + "  |");
			else 
				System.out.print("  " + table[i] + "  |");
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

	//Random digit generator
	static int[] randomTable(int []table) {
		int i;

		for(i = 0; i < table.length; i++) {
			table[i] = (int)(Math.random() * 10);
		}

		return(table);
	}
