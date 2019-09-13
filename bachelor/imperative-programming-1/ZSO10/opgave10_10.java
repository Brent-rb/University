//opgave10_10.java
//Schrijf een programma dat 10 getallen in een tabel inleest en dan nagaat of ze geordend zijn van klein naar groot.
//Schrijf uit op welke positie zich de eerste anomali voordoet.
// let er op dat het programma niet buiten de grenzen van de tabel loop!
//zorg ervoor dat het programma onmiddelijk stopt wanneer je weet dat de tabel niet geordend is.

import tio.*;

class opgave10_10 {
	public static void main(String[] args) {
		int []a = new int [10];
		int i, vorigGetal;
		boolean isGeordend = true;
		System.out.println("Geef 10 getallen");
		for (i = 0; i < a.length ; i++) {
			System.out.println("Geef getal " + (i+1));
			a[i] = Console.in.readInt();
		}
		System.out.println("Controleren of het geordend is...");
		vorigGetal = a[0];
		for (i = 1; i < a.length && isGeordend; i++) {
			if (vorigGetal > a[i])
				isGeordend = false;
			else {
				System.out.println("Getal " + (i+1) + " is OK!");
				vorigGetal = a[i];
			}
		}
		if (!isGeordend)
			System.out.println("Getal " + (i) + " is een anomalie");
	}
}