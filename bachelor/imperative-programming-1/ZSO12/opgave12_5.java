//opgave12_5.java

import tio.*;

class opgave12_5 {
	public static void main(String [] args) {
		int input, row, colomn, spacesCount, i;
		String spaces;
		//System.out.println("Geef de dimensies in");
		//input inlezen
		input = Console.in.readInt();
		//tabel aanmaken met input x input dimensies
		int table[][] = new int [input][input];

		//tabel invullen
		for (row = 0; row < table.length; row++) {
			for (colomn = 0; colomn < table[row].length; colomn++) {
				table[row][colomn] = (int)((Math.random() * 10000.0) + 1);
				System.out.print(table[row][colomn]);
				spaces = "" + table[row][colomn];
				spacesCount = (7 - spaces.length());
				for (i = 0; i < spacesCount; i++) {
					System.out.print(" ");
				}
			}
		}
	}
}