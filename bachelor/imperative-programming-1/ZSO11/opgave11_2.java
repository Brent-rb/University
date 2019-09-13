//opgave11_2.java
import tio.*;


class opgave11_2 {
	public static void main (String [] args) {
		double totaal, jaar, startbedrag;
		double rente;
		System.out.println("Geef het startbedrag");
		startbedrag = Console.in.readInt();
		System.out.println("Geef de rente in %");
		rente = (1 + (Console.in.readInt() / 100.0));
		System.out.println("Geef het aantal jaar");
		jaar = Console.in.readInt();
		for (int i = 1; i < jaar ; i++) {
			rente *= rente;
		}
		totaal = startbedrag * rente;
		System.out.println(totaal);
	}
}