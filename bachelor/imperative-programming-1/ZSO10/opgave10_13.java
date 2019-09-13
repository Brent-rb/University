//opgave10_13.java

import tio.*;

class opgave10_13 {
	public static void main(String[] args) {
		int n,i,schrapGetal = 2, j,k;
		int []rijGetal; 
		int []nieuweRij;
		int lengteNieuweRij, orgineleLengte, begin;
		System.out.println("Geef een waarde voor n in : (groter dan 0)");
		n = Console.in.readInt();
		rijGetal = new int [n];
		for (i = 0,j = 1; i < rijGetal.length; i++, j++) {
			rijGetal[i] = j;
			System.out.print("" + rijGetal[i] + " ");
		}
		System.out.println();
		orgineleLengte = rijGetal.length;
		lengteNieuweRij = orgineleLengte / 2;
		for (k = 2, begin = 1; k < lengteNieuweRij; k++, begin++) {
			if (k == 2)
				lengteNieuweRij = orgineleLengte / k;
			else 
				lengteNieuweRij = ((orgineleLengte / k) + 1);
			System.out.println("Lengte is " + lengteNieuweRij);
			nieuweRij = new int [lengteNieuweRij];
			for (i = 0, j = 0; i < rijGetal.length && j < nieuweRij.length; i++, j++) {
				if (((i - begin) % k) == 0 && i+1 <rijGetal.length)
					i++; 
				nieuweRij[j] = rijGetal[i];
				System.out.print("" + rijGetal[i] + " ");
			}
			rijGetal = new int [nieuweRij.length];
			for (i = 0; i < rijGetal.length; i++) {
				rijGetal[i] = nieuweRij[i];
			}
			System.out.println();
		}
	}
}