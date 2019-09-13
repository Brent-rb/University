class taak17 {
	public static void main(String []args) {
		if(args.length < 2)
			return;
		if(Integer.parseInt(args[0]) <= 0 || Integer.parseInt(args[1]) <= 0)
			return;
		int testInt1 = Integer.parseInt(args[0]), testInt2 = Integer.parseInt(args[1]);
		if (((testInt1 * testInt2) + 2) != args.length) {
			System.out.println("foutief");
			return;
		}
		int lengthRow = Integer.parseInt(args[0]), lengthColomn = Integer.parseInt(args[1]), rowCount, colomnCount, i = 2, row, colomn, lowestNum;
		int [][]table = new int [lengthRow][lengthColomn];
		boolean first = true, lowest = true;;

		for(rowCount = 0; rowCount < table.length; rowCount++) {
			for(colomnCount = 0; colomnCount < table[rowCount].length && i < args.length; colomnCount++, i++) {
				table[rowCount][colomnCount] = Integer.parseInt(args[i]);

			}
		}

		for(rowCount = 0; rowCount < table.length; rowCount++) {
			for(colomnCount = 0; colomnCount < table[rowCount].length; colomnCount++) {
				if((rowCount > 0 && rowCount < table.length - 1) && (colomnCount > 0 && colomnCount < table[rowCount].length - 1)) {
					lowest = false;
					lowest = checkLowest(table, rowCount, colomnCount);
					if(lowest)
						System.out.print(table[rowCount][colomnCount] + " op positie [" + rowCount + "][" + colomnCount + "]; ");
				}
			}
		}
		System.out.println(); 
	}

	static boolean checkLowest(int [][]table, int x, int y) {
		int row, colomn, lowestNum = table[x][y];
		boolean lowest = true;
		//System.out.println();
		//System.out.println("We zoeken " + lowestNum + " met x " + x + " en y " + y);
		for(row = x - 1; row <= x + 1; row++) {
			for(colomn = y - 1; colomn <= y + 1; colomn++) {
				//System.out.print(table[row][colomn] + "   ");
				if((table[row][colomn] <= lowestNum) && (row != x || colomn != y))
					return(false);
			}
			//System.out.println();
		}
		return(true);
	}
}