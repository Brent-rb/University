//opgave10_8.java
//schrijf een programma dat twee rijen getallen inleest in de tabellen a en b.
//er wordt eerst aan de gebruiker gevraagd uit hoeveel cijfers elke rij bestaat. 
//declareer en creer nu een rij c die de concatenatie is van a en b. bijvoorbeeld, indien a en b de tabbellen 1,2,3 en 4,5 zijn dan is c de tabel 1,2,3,4,5
//auteur : Brent Berghmans 1334252

import tio.*;

class opgave10_8 {
	public static void main(String[] args) {
		int []a;
		int []b;
		int []c;
		int i,k , lengteA, lengteB, lengteC;
		boolean gaNaarB = false;
		System.out.println("Geef de lengte van a in ");
		lengteA = Console.in.readInt();
		a = new int [lengteA];
		for (i = 0; i < lengteA; i++) {
			System.out.println("Geef getal " + (i+1) + " in");
			a[i] = Console.in.readInt();
		}
		System.out.println("Geef de lengte van b in ");
		lengteB = Console.in.readInt();
		b = new int [lengteB];
		for (i = 0; i < lengteB; i++) {
			System.out.println("Geef getal " + (i+1) + " in");
			b[i] = Console.in.readInt();
		}
		lengteC = lengteA + lengteB;
		c = new int [lengteC];
		for (i = 0, k = 0; i < lengteC; i ++, k++){
			if (gaNaarB && k < lengteB)
				c[i] = b[k];
			if (i < lengteA && !gaNaarB)
				c[i] = a[k];
			if (i == lengteB) {
				gaNaarB = true;
				k = -1;
			}
		}
		for (i = 0; i < lengteC ; i++) {
			System.out.println("De waarde van c[" + i + "] is " + c[i]);
		}
	}
}