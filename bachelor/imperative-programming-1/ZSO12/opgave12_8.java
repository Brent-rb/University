//opgave12_8.java

import tio.*;

class opgave12_8 {
	public static void main(String [] args) {
		int input;
		System.out.println("Geef n ");
		input = Console.in.readInt();
		int table [][] = new int [input][input];
		int i = 0,j;
		boolean isMagic = true;
		for (i = 0; i < table.length; i++) {
			for (j = 0; j < table[i].length; j++) {
				System.out.println("Geef het getal in (" + (i+1) + "," + (j+1) + ")");
				table[i][j] = Console.in.readInt();
			}
		}
		int som = 0, somMoet;
		for (i = 0, j = 0; j < table[i].length; j++) {
			som += table[i][j];
		}
		somMoet = som;
		som = 0;
		//System.out.println("Som moet " + somMoet);
		for (i = 0; i < table.length && isMagic ; i++) {
			for (j = 0; j < table[i].length & isMagic ; j ++) {
				som += table[i][j];

			}
			//System.out.println("Som " + som);
			if (som != somMoet)
				isMagic = false;
			som = 0;
		}
		som = 0;
		for (j = 0; j < table.length && isMagic ; j++) {
			for (i = 0; i < table.length && isMagic ; i++) {
				som += table[i][j];
			}
			//System.out.println("Som " + som);
			if (som != somMoet)
				isMagic = false;
			som = 0;
		}
		som = 0;
		for (j = 0, i = 0; j < table.length & isMagic ; j++, i++) {
			som += table[i][j];
		}
		//System.out.println("Som " + som);
		if (som != somMoet)
			isMagic = false;
		som = 0;
		for (j = table.length - 1, i = table.length - 1; j >= 0 && isMagic ; j--, i--) {
			som += table[i][j];
		}
		//System.out.println("Som " + som);
		if (som != somMoet)
			isMagic = false;
		if(isMagic)
			System.out.println("Het is magic");
		else
			System.out.println("het is niet magic");
	}
}