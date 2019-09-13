//opgave12_4.java

import tio.*;

class opgave12_4 {
	public static void main(String[] args) {
		int rij, kolom;
		int 
		int tweeD [][] = new int [10][];
		for (rij = 0; rij < tweeD.length; rij++) {
			tweeD[rij] = new int [rij + 1];
			for (kolom = 0; kolom < tweeD[rij].length ; kolom++) {
				tweeD[rij][kolom] = kolom;
				System.out.print(tweeD[rij][kolom]);
			}
			System.out.println();
		}
	}
}