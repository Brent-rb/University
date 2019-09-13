//opgave13_5.java

import tio.*;

class opgave13_5 {
	public static void main(String[] args) {
		boolean [][]board = new boolean [8][8];
		board = queenGen(board);
		int row, colomn;
		writeBoard(board);
		System.out.println();
		for(row = 0; row < board.length ; row++) {
			for (colomn = 0; colomn < board.length ; colomn++) {
				if(board[row][colomn] == true) {
					check(board, row, colomn);
				}
			}
		}
	}
	static void writeBoard (boolean [][]board) {
		int n1 = board.length;
		int n2 = board[0].length;
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
				if (board[row][colomn]) {
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
	static boolean[][] queenGen(boolean [][]board) {
		int randomDigit, row, colomn;
		int queenCounter = 0;
		while(queenCounter < 8) {
			board[(int)(Math.random() * 8)][(int)(Math.random() * 8)] = true;
			queenCounter++;
		}
		return(board);
	}

	static void check(boolean[][] board ,int x, int y) {
		int row, colomn;
		boolean queenFound = false;
		//Onder checken als hij niet op de rand staat
		if (x < board.length) {
			for(row = (x + 1), colomn = y; row < board.length && !queenFound; row++) {
				if (board[row][colomn] == true){
					queenFound = true;
					System.out.println("De koningin op (" + (x + 1) + "," + (y + 1) + ") kan de koningin op (" + (row + 1) + "," + (colomn + 1) + ") slaan");
				}
			}
		}
		//Reset
		queenFound = false;
		//Links checken als hij niet op de rand staat
		if (y < board.length) {
			for(row = x, colomn = (y + 1); colomn < board.length && !queenFound; colomn++) {
				if (board[row][colomn] == true){
					queenFound = true;
					System.out.println("De koningin op (" + (x + 1) + "," + (y + 1) + ") kan de koningin op (" + (row + 1) + "," + (colomn + 1) + ") slaan");
				}
			}
		}
		//Reset
		queenFound = false;
		//Rechts vanboven checken als hij niet op de hoek staat
		if (x > 0  && y < board.length) {
			for(row = (x - 1), colomn = (y + 1); row >= 0 && colomn < board.length && !queenFound; row--, colomn++) {
				if (board[row][colomn] == true){
					queenFound = true;
					System.out.println("De koningin op (" + (x + 1) + "," + (y + 1) + ") kan de koningin op (" + (row + 1) + "," + (colomn + 1) + ") slaan");
				}
			}
		}
		//Reset
		queenFound = false;
		//Rechts onder checken als hij niet op de hoek staat 
		if (x < board.length && y < board.length) {
			for (row = (x + 1), colomn = (y + 1); row < board.length && colomn < board.length && !queenFound; row++, colomn++) {
				if (board[row][colomn] == true) {
					queenFound = true;
					System.out.println("De koningin op (" + (x + 1) + "," + (y + 1) + ") kan de koningin op (" + (row + 1) + "," + (colomn + 1) + ") slaan");
				}
			}
		}
	}
}