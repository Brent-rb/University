import tio.*;

class opgave8_15 {
	public static void main (String[] args) {
		//variabelen declareren 
		int gegevenGetal, i, deeltal;
		boolean isPriem;

		//getal inlezen
		System.out.println("Geef een getal in");
		gegevenGetal = Console.in.readInt();
		

		if (!(priemControle(gegevenGetal))) {
		for (i = (gegevenGetal / 2); i >= 2 ; i--) {
			//Deler zoek functie oproepen
			deeltal = delerZoeken(i , gegevenGetal);
			
	
			//controleren of deeltal priem is
			if (deeltal == 2)
				isPriem = true;
			else
				isPriem = priemControle(deeltal);

			//als het priem is, de deler afdrukken
			if (isPriem) {
				System.out.print("" + deeltal + " ");
				//volgende lus klaar zetten
				gegevenGetal /= deeltal;
				i = gegevenGetal + 1;
				//nodig voor als het ingevoerde getal zelf priem is
			}
		}
		System.out.println();
		}
		else 
		System.out.println(gegevenGetal);
	}
	

	//functie voor deler zoeken
	static int delerZoeken(int deeltal, int gegevenGetal) {
		int i;
		boolean delerGevonden = false;
		for (i = deeltal; !delerGevonden && i >= 2 ; i--) {
			delerGevonden = (gegevenGetal % i) == 0;
			if (delerGevonden)
			i++;
		}
		return(i);
	}
	static boolean priemControle(int deeltal) {
		int i;
		boolean isPriem = true;
		for (i = deeltal - 1; isPriem && i >= 2 ; i--) {
			isPriem = (deeltal % i != 0);
		}
		return(isPriem);
	}
}
