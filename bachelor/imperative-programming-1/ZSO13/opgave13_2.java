//opgave13_2.java

import tio.*;

class opgave13_2 {
	public static void main(String[] args) {
		int input, i, n = 5;
		System.out.println("Geef de dimensies");
		n = Console.in.readInt();
		System.out.println("Geef het aantal iteraties");
		input = Console.in.readInt();
		boolean [][]populatie = new boolean[n][n];
		genRandom(populatie);
		for (i = 1; i <= input; i++) {
			System.out.println("Iteratie: " + i);
			System.out.println("*---------*");
			writePop(populatie);
			if (i != input)
				System.out.println("\n*---------*");
			populatie = makeNext(populatie);
		}
	}


	static void genRandom(boolean [][]populatie) {
		int row, colomn, cellGen = 0;
		int n = populatie.length;
		boolean cellGenBool = false;
		//Ga de rijen af
		for (row = 1; row < n - 1; row++) {
			//Ga de rijen af
			for (colomn = 1; colomn < n - 1; colomn++) {
				//willekeurig 1 of 0 genereren
				cellGen = (int)(Math.random() * 2);
				//is het 1 dan wordt de boolean true
				if (cellGen == 1) 
					cellGenBool = true;
				//anders wordt hij false
				else
					cellGenBool = false;
				//boolean op de juiste plaats zetten
				populatie[row][colomn] = cellGenBool;
			}
		}
	}


	static void writePop (boolean [][]populatie) {
		int n = populatie.length;
		int row, colomn, i = 0;
		for (row = 0; row < n; row++) {
			for(i = 0; i < n; i++) {
				if(row == 0) {
					if (i < n)
						System.out.print(" _____");
					if (i == n-1) {
						System.out.println();
					}
				}
			}
			for (i = 0; i < n; i++) {
				if (i == 0) 
					System.out.print("|     |");
				else
					System.out.print("     |");
			}
			System.out.println();
			for (colomn = 0; colomn < n; colomn++) {
				if (populatie[row][colomn] == true) {
					if(colomn != n-1)
						System.out.print("|  *  ");
					else
						System.out.println("|  *  |");
				}
				else {
					if(colomn != n-1)
						System.out.print("|     ");
					else
						System.out.println("|     |");
				}
			}
			for (i = 0; i < n; i++) {
				if(i == 0)
					System.out.print("|_____|");
				else
					System.out.print("_____|");
			}
			System.out.println();
		}
	}

	static int calcNearby (boolean [][]populatie, int posx, int posy) {
		int n = populatie.length;
		int row, colomn, i = 0, nearby = 0;
		//Kijkt naar de 3x3 Matrix rond het getal als die bestaat anders naar de wel bestaande en niet zichzelf
		for(row = -1; row <= 1; row++) {
			for(colomn = -1; colomn <= 1; colomn++) {
				if ((row != 0 || colomn != 0) && ((posx + row >= 0) && (posx + row <= n-1) && (posy + colomn >= 0) && (posy + colomn <= n-1))) {
					if(populatie[(posx + row)][(posy + colomn)] == true)
						nearby++;
				}
			}
		}
		return(nearby);	
	}


	static boolean[][] makeNext (boolean [][]populatie) {
		int n = populatie.length;
		boolean [][] next = new boolean[n][n];
		int row, colomn, i = 0;

		for(row = 1; row < n - 1; row++) {
			for(colomn = 1; colomn < n - 1; colomn++) {
				if(populatie[row][colomn] == false) {
					if (calcNearby(populatie, row, colomn) == 3)
						next[row][colomn] = true;
				}
				else {
					if(calcNearby(populatie, row, colomn) == 2 || calcNearby(populatie, row, colomn) == 3) 
						next[row][colomn] = true;
					else 
						next[row][colomn] = false;
				}
			}
		}
		return(next);
	}
}