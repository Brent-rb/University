class substringtest {
	public static void main(String[] args) {
		String gegevenString, gegevenSubstring = "", hoogsteVerschilSubstring="", hoogsteGelijkSubstring="";
		//declareren van variabelen
		int i = 0, aantalGelijk = 0, aantalVerschil = 0, hoogsteVerschil = 0, hoogsteGelijk = 0;
		if (args.length != 1)
			return;
		
		//inlezen van string
		gegevenString = args[0];
		if (gegevenString.length() == 0)
			return;
	
		//begin lus
		while (i < gegevenString.length()) {
			//substring aanmaken tot hij een spatie tegenkomt
			while (i < gegevenString.length() && ((gegevenString.charAt(i) >= 'a' && gegevenString.charAt(i) <= 'z') || (gegevenString.charAt(i) >= 'A' && gegevenString.charAt(i) <= 'Z'))) {
				gegevenSubstring += gegevenString.charAt(i);
				i++;
			}
			//klaarzetten voor volgende stap want charAt(i) is momenteel een spatie
			i++;



			//aantal letters die hetzelfde zijn zoeken			
			aantalGelijk = gelijkmethode(gegevenSubstring);
			//Bijhouden van het grootste aantal gelijke letters
			if (aantalGelijk > hoogsteGelijk) {
				hoogsteGelijk = aantalGelijk;
				hoogsteGelijkSubstring = gegevenSubstring;
			}



			//aantal verschillende letters zoeken
			aantalVerschil = verschilmethode(gegevenSubstring);
			//Bijhouden van het grootste aantal verschillende letters
			if (aantalVerschil > hoogsteVerschil) {
				hoogsteVerschil = aantalVerschil;
				hoogsteVerschilSubstring = gegevenSubstring;
			}


			//reset van substring voor volgende stap
			gegevenSubstring = "";
		}
		System.out.println("Maximaal aantal verschillende letters: " + hoogsteVerschilSubstring);
		System.out.println("Maximaal voorkomen van een letter: " + hoogsteGelijkSubstring);

	}


	static int gelijkmethode (String gegevenSubstring) {
		char hulpletter;
		int i, k, aantalGelijk = 0, hoogsteGelijk = 0;


		//substring lokaal omzetten naar kleine letters
		gegevenSubstring = tolowercase(gegevenSubstring);


		//Lus die voor elke letter van de substring nagaat hoeveel keer hij er in zit		
		for (i = 0; i < gegevenSubstring.length(); i++) {
			hulpletter = gegevenSubstring.charAt(i);


			for (k = 0; k < gegevenSubstring.length(); k++) {
				if (gegevenSubstring.charAt(k) == hulpletter)
					aantalGelijk++;
			}


			//hoogste waarde telt dus dit is de enigste waarde die we moeten bijhouden
			if (hoogsteGelijk < aantalGelijk)
				hoogsteGelijk = aantalGelijk;
			aantalGelijk = 0;


		}
		return(hoogsteGelijk);
	}


	static int verschilmethode (String gegevenSubstring) {
		char hulpletter;
		boolean zitErIn = false;
		int i, k, aantalVerschil = 0, hoogsteVerschil = 0;


		gegevenSubstring = tolowercase(gegevenSubstring);

		//lus die alle letters van a - z afgaat en kijkt of ze er in zitten 
		for (i = 'a' ; i <= 'z' ; i++) {
			hulpletter = (char)(i);

			//kijken of de letter er in zit
			for (k = 0; k < gegevenSubstring.length() && !zitErIn ; k++) {
				if (gegevenSubstring.charAt(k) == hulpletter)
					zitErIn = true;
			}

			//zo ja aantal verschillende letters verhogen met 1
			if (zitErIn)
				aantalVerschil++;

			//resetten voor volgende stap
			zitErIn = false;
		}
		return(aantalVerschil);
	}

	//lower case functie voor het vergemakkelijken van andere lussen 
	static String tolowercase (String gegevenSubstring) {
		char hulpletter;
		String lowercase = "";
		int i;

		//neemt elke letter en kijkt of hij tussen A en Z zit
		for (i = 0; i < gegevenSubstring.length(); i++) {
			hulpletter = gegevenSubstring.charAt(i);

			//als het een hoofdletter is - A doen en + a 
			if (hulpletter >= 'A' && hulpletter <= 'Z') 
				hulpletter = (char)((hulpletter - 'A') + 'a');
			lowercase += "" + hulpletter;
		}
		return(lowercase);
	}
	
}
		

