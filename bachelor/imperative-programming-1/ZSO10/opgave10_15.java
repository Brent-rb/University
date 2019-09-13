//opgave10_15.java

import tio.*;

class opgave10_15 {
	public static void main(String[] args) {
		int []rij1;
		int []rij2;
		int []resultaatrijLeft;
		int []resultaatrijRight;
		int []resultaatrij;
		String string1, string2, getalString ="";
		int i,j,k,getal, getalTeller=0, getalTeller2=0, hoogsteGetal = -9999999;
		System.out.println("Geef rij 1 in: 1 2 3 4 5 .... 50 51");
		string1 = Console.in.readLine();
		System.out.println("Geef rij 2 in zoals rij 1");
		string2 = Console.in.readLine();
		for (i = 0, j = 0; i < string1.length(); j++, i++) {
			while (i < string1.length() && string1.charAt(i) != ' ') {
				getalString += ""+ string1.charAt(i);
				i++;
			}
			getalTeller++;
			getalString = "";
		}
		for (i = 0, j = 0; i < string2.length(); j++, i++) {
			while (i < string2.length() && string2.charAt(i) != ' ') {
				getalString += ""+ string2.charAt(i);
				i++;
			}
			getalTeller2++;
			getalString = "";
		}
		rij1 = new int [getalTeller];
		rij2 = new int [getalTeller2];
		//System.out.println("Getal teller " + getalTeller);
		for (i = 0, j = 0; j < getalTeller; j++, i++) {
			while (i < string1.length() && string1.charAt(i) != ' ') {
				getalString += ""+ string1.charAt(i);
				i++;
			}
			getal = naarInt(getalString);
			if (getal > hoogsteGetal)
				hoogsteGetal = getal;
			rij1[j] = getal;
			//System.out.println("Rij 1 plaats " + j + " staat " + rij1[j]);
			getalString = "";
		}
		for (i = 0, j = 0; j < getalTeller2; j++, i++) {
			while (i < string2.length() && string2.charAt(i) != ' ') {
				getalString += ""+ string2.charAt(i);
				i++;
			}
			getal = naarInt(getalString);
			if (getal > hoogsteGetal)
				hoogsteGetal = getal;
			rij2[j] = getal;
			//System.out.println("Rij 2 plaats " + j + " staat " + rij2[j]);
			getalString = "";
		}
		resultaatrijLeft = new int [hoogsteGetal+1];
		resultaatrijRight = new int [hoogsteGetal+1];
		for (i = 0; i < resultaatrijLeft.length; i++) {
			for (j = 0; j < rij1.length ; j++) {
				if (rij1[j] == i)
					resultaatrijLeft[i]++;
			}
		}
		for (i = 0; i < resultaatrijRight.length; i++) {
			for (j = 0; j < rij2.length ; j++) {
				if (rij2[j] == i)
					resultaatrijRight[i]++;
			}
		}
		resultaatrij = new int [hoogsteGetal+1];
		for (i = 0; i < resultaatrij.length; i++) {
			if (resultaatrijLeft[i] <= resultaatrijRight[i])
				resultaatrij[i] = resultaatrijLeft[i];
			else
				resultaatrij[i] = resultaatrijRight[i];
		}
		for (i = 0; i < hoogsteGetal+1; i++) {
			for (j = 0; j < resultaatrij[i]; j++) {
				if (i == hoogsteGetal && j == resultaatrij[i] -1) 
					System.out.println("" + i);
				else
					System.out.print("" + (i) + ",");
			}
		}
	}
	static int naarInt(String getalString) {
		int i,nulteller, k, lengte, getal, som = 0;
		lengte = getalString.length();
		for (i = lengte - 1, nulteller = 0; i >= 0; i--, nulteller++) {
			getal = (getalString.charAt(i) - '0');
			for (k = 0; k < nulteller; k++) {
				getal *= 10;
			}
			som += getal;
		}
		return(som);
	}
}