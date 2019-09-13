//Taak7_1.java
//Tell de getallen die voorkomen in een string op
//Auteur Brent Berghmans 1334252

class Taak7_1 {
		public static void main(String[] args) {
			//begin initiatie
			String gegevenString, getalString = ""; 
			int teller, getal, intGetal, som = 0;
			if (args.length < 1)
				return;
			gegevenString = args[0];
			//Einde initiatie
			for (teller = 0; teller < gegevenString.length(); teller++) {
				if (gegevenString.charAt(teller) >= '0' && gegevenString.charAt(teller) <= '9') {
					//als getal detecteerd zet deze in een string en de getallen er achter
					getalString = getalstacker(teller, gegevenString);
					intGetal = intomzetter(getalString);
					som += intGetal;
					while (teller < gegevenString.length() && gegevenString.charAt(teller) >= '0' && gegevenString.charAt(teller) <= '9'){
						teller++;
					}
				}
			}
			System.out.println(som);
		}
		static String getalstacker (int teller, String gegevenString) {
			int i = teller;
			String getalString = "";
			char controle;
			if ((teller -1) >= 0)
				controle = gegevenString.charAt(teller -1);
			else
				controle = gegevenString.charAt(teller);
			if ((!((controle >= 'a' && controle <= 'z') || (controle >= 'A' && controle <= 'Z'))  || (teller == 0))) {
				for (i = teller; i < gegevenString.length() && gegevenString.charAt(i) >= '0' && gegevenString.charAt(i) <= '9' ; i ++) {
					getalString += "" + gegevenString.charAt(i);
				}
			}
			if (i >= 0 && i < gegevenString.length())
				controle = gegevenString.charAt(i);
			if (((controle >= 'a' && controle <= 'z') || (controle >= 'A' && controle <= 'Z')))
				getalString = "0";
			return(getalString);
		}
		static int intomzetter(String gegevenString) {
			int i, nulteller, getal = 0, nul = 1, k;
			for(i = 0, nulteller = gegevenString.length(); i < gegevenString.length(); i++, nulteller--) {
				for (k = 1; k < nulteller; k++) {
					nul *= 10;
				}

				getal = getal + ((int)((gegevenString.charAt(i) - '0')) * nul);
				nul = 1;
			}
			return(getal);
		}
	}
