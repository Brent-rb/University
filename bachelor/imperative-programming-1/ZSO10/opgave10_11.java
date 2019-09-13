//opgave10_11.java

import tio.*;

class opgave10_11 {
	public static void main(String[] args) {
		int []a = new int [10];
		int i, getal;
		long derp = 1000000000;
		for (i = 1; i <= derp; i++) {
			getal = (int)((double)((Math.random() * 10.0)));
			a[getal]++;
			//System.out.print(getal);
		}
		for (i = 0; i < a.length; i++) {
			a[i] /= 10000000;
			System.out.println("Getal " + i + " komt procentueel " + a[i] + "% keer voor");
		}
	}
}
