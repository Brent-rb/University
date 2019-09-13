//opgave13_4.java
import tio.*;


class opgave13_4 {
	public static void main(String[] args) {
		int dimensionx, dimensiony;
		System.out.println("Geef de dimensie rij");
		dimensionx = Console.in.readInt();
		System.out.println("Geef de dimensie kolom");
		dimensiony = Console.in.readInt();
		int [][]sky = new int [dimensionx][dimensiony];
		sky = heelal(dimensionx, dimensiony);
		sky = makeStar(sky, dimensionx, dimensiony);
		writePop(sky);


	}
	static int[][] heelal(int dimensionx, int dimensiony) {
		int [][]sky = new int[dimensionx][dimensiony];
		int row, colomn, skyGen = 0;
		//Ga de rijen af
		for (row = 0; row < sky.length; row++) {
			//Ga de rijen af
			for (colomn = 0; colomn < sky[row].length; colomn++) {
				//willekeurig getal genereren
				skyGen = (int)(Math.random() * 101.0);
				sky[row][colomn] = skyGen;
			}
		}
		return(sky);
	}

	static void writePop (int [][]sky) {
		int n1 = sky.length;
		int n2 = sky[0].length;
		int row, colomn, i = 0;
		int amountStars = 0;
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
				if (sky[row][colomn] >= 150) {
					amountStars++;
					if(colomn != n2-1)
						System.out.print("|  *  ");
					else
						System.out.println("|  *  |");
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
		System.out.println("Het aantal sterren: " + amountStars);
	}

	static int calcNearby (int [][]sky, int posx, int posy) {
		int n1 = sky.length - 1;
		int n2 = sky[0].length - 1;
		int row, colomn, i = 0, nearby = 0;
		if (posx - 1 >= 0)
			nearby += sky[(posx - 1)][posy];
		else
			nearby += sky[(n1 -1)][posy];
		if (posx + 1 < n1)
			nearby += sky[(posx + 1)][posy];
		else
			nearby += sky[0][posy];
		if (posy - 1 >= 0)
			nearby += sky[posx][(posy - 1)];
		else
			nearby += sky[posx][(n2 - 1)];
		if (posy + 1 < n2)
			nearby += sky[posx][(posy + 1)];
		else
			nearby += sky[posx][0];
		return(nearby);	
	}


	static int[][] makeStar (int [][]sky, int n1, int n2) {
		int [][] next = new int[n1][n2];
		int row, colomn, i = 0;

		for(row = 0; row < n1; row++) {
			for(colomn = 0; colomn < n2; colomn++) {
				next[row][colomn] = calcNearby(sky, row, colomn);
			}
		}
		return(next);
	}
}