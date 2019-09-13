//opgave15_8_4.java

import tio.*;

class opgave15_8_4 {
	public static void main(String[] args) {
		int length, i;
		char []alfabet = new char[4];
		alfabet[0] = 'A';
		alfabet[1] = 'C';
		alfabet[2] = 'T';
		alfabet[3] = 'G';
		String [][]table = new String[10][3];
		for(i = 0; i < table.length ; i++) {
			table[i] = genRandom(alfabet);
			System.out.println("Rij " + i + " heeft " + table[i]);
		}
	}

	static void writeAll(String answerString, int index, char[] alfabet) {
		int i;

		if(index > 0) {
			for(i = 0; i < alfabet.length; i++) {
				writeAll(answerString + alfabet[i], index - 1, alfabet);
			}
		}
		else{
			System.out.println(answerString);
			return;
		}
		return;
	}

	static String genRandom(char []table) {
		int i;
		String randomString = "";
		for(i = 0; i < 20; i++) {
			randomString += "" + table[(int)(Math.random() * table.length)];
		}
		return(randomString);
	}
}
