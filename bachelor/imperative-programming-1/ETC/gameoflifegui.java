//opgave13_2.java

import tio.*;
import be.uhasselt.util.*;
import be.uhasselt.gui.*;

class gameoflifegui {
	public static void main(String[] args) {
		int input, i, n = 5, row, column;
		row = Integer.parseInt(args[0]);
		column = Integer.parseInt(args[1]);

		boolean [][]populatie = new boolean[row][column];
		genRandom(populatie);

		//ImageGrid aanmaken met hoogte en breedte gebasseerd op het mineField
		ImageGrid.createGrid(populatie.length, populatie[0].length, 3, 3);
		//Image path zetten
		ImageGrid.setImagePath("./images");
		//Elke rij afgaan
		for(row = 0; row < populatie.length; row++) {
			//Elke kolom afgaan 
			for(column = 0; column < populatie[row].length; column++) {
				if(populatie[row][column])
					ImageGrid.setColor(row, column, 0, 0, 0);
				else
					ImageGrid.setColor(row, column, 255, 255, 255);
			}
		}
		//ImageGrid tonen
		ImageGrid.showGrid();
			
		for (i = 1; i <= 1;) {
			for(row = 0; row < populatie.length; row++) {
				//Elke kolom afgaan 
				for(column = 0; column < populatie[row].length; column++) {
					if(populatie[row][column])
						ImageGrid.setColor(row, column, 0, 0, 0);
					else
						ImageGrid.setColor(row, column, 255, 255, 255);
				}
			}
			ImageGrid.refresh();
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
			for (colomn = 1; colomn < populatie[row].length - 1; colomn++) {
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

	static int calcNearby (boolean [][]populatie, int posx, int posy) {
		int n = populatie.length;
		int row, colomn, i = 0, nearby = 0;
		//Kijkt naar de 3x3 Matrix rond het getal als die bestaat anders naar de wel bestaande en niet zichzelf
		for(row = -1; row <= 1; row++) {
			for(colomn = -1; colomn <= 1; colomn++) {
				if ((row != 0 || colomn != 0) && ((posx + row >= 0) && (posx + row <= n-1) && (posy + colomn >= 0) && (posy + colomn <= populatie[0].length))) {
					if(populatie[(posx + row)][(posy + colomn)] == true)
						nearby++;
				}
			}
		}
		return(nearby);	
	}


	static boolean[][] makeNext (boolean [][]populatie) {
		int n = populatie.length;
		boolean [][] next = new boolean[populatie.length][populatie[0].length];
		int row, colomn, i = 0;

		for(row = 1; row < next.length - 1; row++) {
			for(colomn = 1; colomn < next[row].length - 1; colomn++) {
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