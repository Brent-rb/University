import tio.*;
import be.uhasselt.util.*;
import be.uhasselt.gui.*;

class gui1 {
	public static void main(String[] args) {
		int input, i, n = 5, row, column;
		row = Integer.parseInt(args[0]);
		column = Integer.parseInt(args[1]);

		boolean [][]populatie = new boolean[row][column];

		//ImageGrid aanmaken met hoogte en breedte gebasseerd op het mineField
		ImageGrid.createGrid(populatie.length, populatie[0].length, 3, 3);
		//Image path zetten
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
		while(true) {
			for(int s = 0; s < 100; s++)
				for(int j = 0; j < 100; j++)
					if(populatie[s][j])
						ImageGrid.setColor(s, j, 0, 0, 0);
					else
						ImageGrid.setColor(s, j, 255, 255, 255);
			move(populatie, 0, 0);
			ImageGrid.refresh();

		}
		
	}

	public static void move(boolean [][]populatie, int x, int y) {
		if(x < 0 || y < 0)
			return;
		if(x >= populatie.length || y >= populatie[x].length)
			return;
		
		populatie[(int)Math.random() % 100][(int)Math.random() % 100] = (Math.random() % 10 > 5 ? true : false);
	}
}