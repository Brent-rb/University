//Oef 14.9

import tio.*;

class remake1 {
	public static void main(String[] args) {
		int getal, teller;
		int[] tabel;
		System.out.println("Geef een getal");
		getal = Console.in.readInt();
		tabel = new int[getal];
		for (teller = 0; teller < getal; teller++) {
			tabel[teller] = 4 * teller;
		}
		System.out.println("De som is " + Som(tabel));
	}

	static int Som(int[] tabel) {
		return(SomIndex(tabel,0));
	}

	static int SomIndex(int[] table, int index) {
		if(index >= table.length)
			return(0);

		int sum = table[index] + SomIndex(table, index + 1);

		return(sum);
	}
}