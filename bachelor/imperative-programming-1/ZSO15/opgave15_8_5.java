//opgave15_8_5.java

//opgave15_8_4.java

import tio.*;

class opgave15_8_5 {
	public static void main(String[] args) {
		int length, i,j, distance1, distance2, distance3;
		String string1, string2;
		int distance = 0;
		char []alfabet = new char[4];
		boolean placeFound = false;
		alfabet[0] = 'A';
		alfabet[1] = 'C';
		alfabet[2] = 'T';
		alfabet[3] = 'G';
		String []smallTable = new String[10];
		String [][]bigTable = new String[10][3];

		//SmallTable initializeren
		for(i = 0; i < smallTable.length ; i++) {
			smallTable[i] = genRandom(alfabet);
			System.out.println(smallTable[i]);
		}

		//BigTable initializeren
		for(i = 0; i < bigTable.length ; i++) {
			for(j = 0; j < bigTable[i].length; j++) {
				bigTable[i][j] = "a";
			}
		}
		//SmallTable met BigTable vergelijken 
		for(i = 0; i < smallTable.length; i++) {
			string1 = smallTable[i];
			for(j = 0; j < smallTable.length; j++) {
				if(j == i)
					continue;
				string2 = smallTable[j];
				distance = checkWrong(string1, string2);

				if(distance < checkWrong(string1, bigTable[i][0]) && !placeFound) {
					bigTable[i][0] = string2;
					placeFound = true;
				}
				if(distance < checkWrong(string1, bigTable[i][1]) && !placeFound) {
					bigTable[i][1] = string2;
					placeFound = true;
				}
				if(distance < checkWrong(string1, bigTable[i][2]) && !placeFound) {
					bigTable[i][2] = string2;
					placeFound = true;
				}
				sortRow(bigTable, string1, i);
				placeFound = false;
			}
		}

		//BigTable afdrukken voor controle
		for(i = 0; i < bigTable.length ; i++) {
			for(j = 0; j < bigTable[i].length; j++) {
				System.out.print("Afstand is :"+ checkWrong(smallTable[i], bigTable[i][j]) + " ");
				System.out.println(bigTable[i][j]);
			}
		}
	}

	static String genRandom(char []table) {
		int i;
		String randomString = "";
		//Random string genereren van lengte 20
		for(i = 0; i < 20; i++) {
			randomString += "" + table[(int)(Math.random() * table.length)];
		}
		return(randomString);
	}

	static int checkWrong(String string1, String string2) {
		int distance = 0;
		int extra = 0;
		//Distance checker
		if (string1.length() < string2.length()) {
			extra = string2.length() - string1.length();
			string2 = string2.substring(0,string1.length());
		}
		if (string1.length() > string2.length()) {
			extra = string1.length() - string2.length();
			string1 = string1.substring(0, string2.length());
		}
		int length = string1.length();
		if(string1.length() == 0)
			return(0);
		if(string1.charAt(0) != string2.charAt(0)) {
			distance = 1;
		}
		distance += checkWrong(string1.substring(1, length), string2.substring(1, length));
		return(distance + extra);
	}

	static void sortRow(String[][] table, String string1, int row) {
		int i, j;
		int highestDistance, highestPos;
		String hulp;
		for(i = 0; i < table[row].length; i++) {
			highestDistance = checkWrong(string1, table[row][i]);
			hulp = table[row][i];
			highestPos = i;
			for(j = i + 1; j < table[row].length; j++) {
				if(checkWrong(string1, table[row][j]) > highestDistance) {
					highestDistance = checkWrong(string1, table[row][j]);
					highestPos = j;
				}
			}
			table[row][i] = table[row][highestPos];
			table[row][highestPos] = hulp;
		}
	}
}
