//Doel: Het maken van een library die we kunnen gebruiken in hierna komende oefeningen

/**
*@author Brent Berghmans 1ste Bachelor Informatica 2013-2014
*/


class EpicLibrary {
	/*	                   	*\
	|Begin getRandom functie |
	\*                     	*/

	//Doel: genereert een willekeurige waarde tussen het gesloten interval [a,b]

	/**
	*Een functie die een willekeurig getal tussen het gesloten interval [a,b] genereert.
	*@param a Type: int Doel: ondergrens van het gesloten interval [a,b] specifieeren, we gaan er van uit dat dit een positief getal is
	*@param b Type: int Doel: bovengrens van het gesloten interval [a,b] specifieeren, we gaan er van uit dat dit een positief getal is
	*@return Een willekeurig getal tussen het gesloten interval [a,b]
	*/
	public static int getRandom(int a, int b) {
		//Als de getallen negatief zijn --> omzetten naar positieve getallen
		if(a < 0)
			a *= -1;
		if(b < 0)
			b *= -1;
		//a mag niet grooter zijn dan b aangezien a de ondergrens is en b de bovengrens
		if(a > b)
			return(0);
		//Als we add toevoegen aan Math.random krijgen we een ondergrens van add aangezien math.random van [0,1[ gaat, als we hier 5 bij optellen krijgen we een ondergrens van 5;
		int add = a;
		//Als we Math.random vermenigvuldigen met multiply krijgen we de bovengrens - 1 vb voor b = 5 [0,1[ * (5 +1) = [0,6[ = [0,5] (wegens int), -a anders krijgen we een verkeerde bovengrens. 
		int multiply = (b - a) + 1;
		//Return de uitkomst 
		return((int)((Math.random() * multiply) + add));
	}
	/*	                   	*\
	|Einde getRandom functie |
	\*                     	*/

	/*	                   			*\
	|Begin generateBoolTable functie |
	\*                     			*/
 
	/**
	*Een functie die een m*n tabel genereert met t willekeurige cellen die op 'true' staan
	*@param m Type: int Doel: het aantal rijen specifieeren, we gaan er van uit dat dit een positief getal is 
	*@param n Type: int Doel: het aantal kolommen specifieeren, we gaan er van uit dat dit een positief getal is
	*@param t Type: int Doel: het aantal cellen die willekeurig op 'true' worden gezet, we gaan er van uit dat dit een positief getal is
	*@return Een m*n tabel met t willekeurige cellen die op true staan
	*/
	public static boolean [][] generateBoolTable(int m, int n, int t) {
		
		
		//Als de getallen negatief zijn --> omzetten naar positieve getallen
		if(m < 0)
			m *= -1;
		if(n < 0)
			n *= -1;
		if(t < 0)
			t *= -1;
		//Het aantal cellen op true mag niet groter zijn dan het aantal cellen --> t = aantal cellen
		if(t > (m*n))
			t = m*n;
		//Nieuwe tabel aanmaken met m rijen en n kolommen
		boolean [][]table = new boolean[m][n];
		//teller, random plaats op de rij, random plaats op de kolom
		int i = 0, randomRow, randomColomn;
		while (i < t) {
			//Random rij nummer genereren
			randomRow = (int)(Math.random() * m);
			//Random kolom nummer genereren
			randomColomn = (int)(Math.random() * n);
			//Checken of die plaats nog op false staat
			if(!table[randomRow][randomColomn]) {
				//Zo ja --> zetten we die plek op true en verhogen we i
				table[randomRow][randomColomn] = true;
				i++;
			}
			else
				//zo niet gaan we naar de volgende iteratie zodat er weer een random rij en kolomn wordt gegenereert
				continue;

		}
		return(table);
	}
	/*	                   			*\
	|Einde generateBoolTable functie |
	\*   							*/



	/*	                   			*\
	|Begin convertBool2D1D	 functie |
	\*                     			*/
	/**
	*Een functie die 2D tabel converteert naar een 1D Tabel waarbij alle rijen achter mekaar staan;
	*@param t Type: boolean[][] Doel: De tabel die geconverteerd moet worden, we verwachten een niet lege tabel.
	*@return De geconverteerde 1D tabel.
	*/
	public static boolean[] convertBool2D1D(boolean[][] t) {
		//lengte bepalen van alle kolommen, teller, rijteller, kolomteller
		int length = 0, i = 0, row, colomn;
		//nieuwe 1D table
		boolean []table = new boolean[0];
		//Als hij 0 rijen en 0 kolommen heeft een lege tabel terug sturen
		if(t.length < 1)
			return(table);
		for(i = 0; i < t.length; i++) {
			//Van elke rij de lengte optellen
			length += t[i].length;
		}
		//Met die lengte een nieuwe tabel maken.
		table = new boolean[length];

		//Elke rij afgaan van orginele tabel
		i = 0;
		for(row = 0; row < t.length; row++) {
			//Elke kolom afgaan van orginele rij
			for(colomn = 0; colomn < t[row].length; colomn++,i++) {
				//Op waarde i van de nieuwe tabel de waarde van t[row][colomn] zetten, i wordt bij zowel de rijen als kolommen +1 gedaan om zo de juiste positie te krijgen
				table[i] = t[row][colomn];
			}
		}

		return(table);

		
	}
	/*	                   			*\
	|Einde convertBool2D1D	 functie |
	\*   							*/


	/*	                   			*\
	|Begin shuffle2D functie 		 |
	\*                     			*/
	/**
	*Een functie die een 2D tabel shufflet met het Fisher-Yates algoritme.
	*@param t Type: boolean[][] Doel: De tabel die geshuffled moet worden met Fisher-Yates, we verwachten een niet lege tabel.
	*/
	public static void shuffle2D(boolean[][] t) {
		//Als we een lege tabel krijgen niks doen.
		if(t.length < 1)
			return;
		//Tijdelijke 1D tabel gebasseerd op de 2D tabel om makkelijker te kunne sorteren
		boolean []temp = convertBool2D1D(t);
		//Onze tellers declareren
		int i = 0,row,colomn;
		shuffle1D(temp);
		//De 2d tabel terug reconstrueren a.d.h.v. de rij 
		for(row = 0; row < t.length ; row++) {
			for(colomn = 0; colomn < t[row].length; colomn++,i++) {
				t[row][colomn] = temp[i];
			}
		}
	}
	/*	                   			*\
	|Einde shuffle2D functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin shuffle1D functie 		 |
	\*                     			*/
	/**
	*Een functie die een 1D tabel shufflet met het Fisher-Yates algoritme.
	*@param t Type: boolean[] Doel: De tabel die geshuffled moet worden met Fisher-Yates, we verwachten een niet lege tabel.
	*/
	public static void shuffle1D(boolean[] t) {
		//Lege input --> niks doen
		if(t.length < 1)
			return;

		//tellers declareren
		int i, place;
		//nieuwe boolean tabel aanmaken
		boolean []boolTable = new boolean[t.length];
		//Hulp variabele maken om 2 booleans te switchen
		boolean temp;
		for(i = t.length - 1; i >= 0; i--) {
			//Getal switchen met een steeds kleiner interval
			place = (int)((Math.random()) * i);
			temp = t[i];
			t[i] = t[place];
			t[place] = temp;
		}
	}
	/*	                   			*\
	|Einde shuffle1D functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin countTrue functie 		 |
	\*                     			*/
	/**
	*Een functie die het aantal true waarden in een matrix telt.
	*@param t Type: boolean[][] Doel: De tabel waarin het aantal true's wordt geteld, we verwachten een niet lege tabel.
	*@return Het aantal true waarden in een matrix.
	*/
	public static int countTrue(boolean[][] t) {
		//Een lege tabel heeft geen waarden dus 0 terugsturen
		if(t.length < 1)
			return(0);
		//Rijteller, kolomteller, true teller
		int row, colomn, amountOfTrue = 0;
		//Elke rij en kolom afgaan
		for(row = 0; row < t.length; row++) {
			for(colomn = 0; colomn < t[row].length; colomn++) {
				//Als de waarde op die plek true is amountOfTrue +1
				if(t[row][colomn])
					amountOfTrue++;
			}
		}

		return(amountOfTrue);
	}
	/*	                   			*\
	|Einde countTrue functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin countTrue functie 		 |
	\*                     			*/
	/**
	*Een functie die het aantal true waarden in een rij telt.
	*@param t Type: boolean[] Doel: De rij waarin het aantal true's wordt geteld, we verwachten een niet lege rij.
	*@return Het aantal true waarden in een rij.
	*/
	public static int countTrue(boolean[] t) {
		//Input controle, lege rij --> 0 trues
		if(t.length < 1)
			return(0);
		//Rijteller, kolomteller, true teller
		int row, colomn, amountOfTrue = 0;
		//Elke rij en kolom afgaan
		for(row = 0; row < t.length; row++) {
			if(t[row])
				amountOfTrue++;
		}

		return(amountOfTrue);
	}
	/*	                   			*\
	|Einde countTrue functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin countFalse functie 		 |
	\*                     			*/
	/**
	*Een functie die het aantal false waarden in een matrix telt.
	*@param t Type: boolean[][] Doel: De tabel waarin het aantal false's wordt geteld, we verwachten een niet lege tabel.
	*@return Het aantal false waarden in een matrix.
	*/
	public static int countFalse(boolean[][] t) {
		//Een lege tabel heeft geen waarden dus ook geen false's --> 0 terugsturen
		if(t.length < 1)
			return(0);
		//Rijteller, kolomteller, false teller
		int row, colomn, amountOfFalse = 0;
		//Elke rij en kolom afgaan
		for(row = 0; row < t.length; row++) {
			for(colomn = 0; colomn < t[row].length; colomn++) {
				//Als de waarde op die plek false is amountOfFalse +1
				if(!t[row][colomn])
					amountOfFalse++;
			}
		}

		return(amountOfFalse);
	}
	/*	                   			*\
	|Einde countFalse functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin boolNot functie 		 	 |
	\*                     			*/
	/**
	*Een functie die een kopie maakt van een boolean table maar met de logische NOT toegepast op iedere waarde.
	*@param t1 Type: boolean[][] Doel: De tabel die geconverteerd moet worden, we verwachten een niet lege tabel.
	*@return De geconverteerde tabel
	*/
	public static boolean[][] boolNot(boolean[][] t1) {
		//input controle
		if(t1.length < 1)
			return(t1);

		//Rijteller, kolomteller, teller
		int row, colomn, i;
		//Nieuwe tabel maken
		boolean [][]table = new boolean[t1.length][];
		//Elke rij afgaan voor de lengte van die kolom te bepalen en aan te maken
		for(i = 0; i < t1.length; i++) {
			table[i] = new boolean [t1[i].length];
		}
		//Elke rij en kolom afgaan om de nieuwe tabel een waarde te geven
		for(row = 0; row < table.length; row++) {
			for(colomn = 0; colomn < table[row].length; colomn++) {
				table[row][colomn] = !t1[row][colomn];
			}
		}

		return(table);
	}
	/*	                   			*\
	|Einde boolNot functie 			 |
	\*   							*/



	/*	                   			*\
	|Begin boolAnd functie 		 	 |
	\*                     			*/
	/**
	*Een functie die een kopie maakt van een boolean table maar met de logische And toegepast op iedere waarde. Als de tabllen verschillend van lengte zijn gaan de missende waarden als false worden geinterpreteert
	*@param t1 Type: boolean[][] Doel: De linker tabel die geconverteerd moet worden, we verwachten een niet lege tabel.
	*@param t2 Type: boolean[][] Doel: De rechter tabel die geconverteerd moet worden, we verwachten een niet lege tabel. 
	*@return De geconverteerde tabel
	*/
	public static boolean[][] boolAnd(boolean[][] t1, boolean[][] t2) {
		//teller
		int i;
		//input controle
		if(t1.length < 1 && t2.length < 1)
			return(t1);
		//Als t1 leeg is en t2 niet wordt er een kopie van t2 gemaakt met alles false aangezien die waarde in t1 mist en vice versa
		if(t1.length < 1 && t2.length >= 1) {
			boolean [][]table = new boolean[t2.length][];
			for(i = 0; i < t2.length; i++) {
				table[i] = new boolean[t2[i].length];
			}
			return(table);
		}
		if(t2.length < 1 && t1.length >= 1) {
			boolean [][]table = new boolean[t1.length][];
			for(i = 0; i < t1.length; i++) {
				table[i] = new boolean[t1[i].length];
			}
			return(table);
		}
		//Rijteller, kolomteller, teller
		int row, colomn;
		//Nieuwe tabel maken
		boolean [][]table;



		//tabel kopie gaan aanmaken gebasseerd op de grootse lengte van 1 v.d 2 tabellen voor zowel lengte als breedte
		if(t1.length > t2.length)
			table = new boolean[t1.length][];
		else
			table = new boolean[t2.length][];

		//Voor de kolommen te bepalen wordt het moeilijker aangezien het programma zou crashen als de rij niet bestaat
		for(i = 0; (i < t1.length || i < t2.length) && i < table.length; i++) {
			//Als de rij teller groter of gelijk aan de lengte van tabel1 is dan moet de nieuwe kolom zowiezo de lengte van tabel 2 hebben.
			if(i >= t1.length)
				table[i] = new boolean[t2[i].length];
			//Het omgekeerde van hierboven
			if(i >= t2.length)
				table[i] = new boolean[t1[i].length];
			//Als de teller nog kleiner is voor de beiden
			else {
				//Als i < lengte tabel 1 & 2 en die rijen bestaan
				if(i < t1.length && i < t2.length && t1.length != 0 && t2.length != 0)
					//Kijken naar welke kolom het langste is op die rij
					if(t1[i].length > t2[i].length)
						table[i] = new boolean[t1[i].length];
					else
						table[i] = new boolean[t2[i].length];
				//Anders kijken welke tabel nog een kolom op die rij heeft
				else {
					if(t1.length == 0 && i < t2.length)
						table[i] = new boolean[t2[i].length];
					else if(t2.length == 0 && i < t1.length)
						table[i] = new boolean[t1[i].length];
				}
			}	
		}


		//Elke rij en kolom afgaan om de nieuwe tabel een waarde te geven
		for(row = 0; row < table.length; row++) {
			for(colomn = 0; colomn < table[row].length; colomn++) {
				//Kijken of de rij plaatsen en kolom plaatsen wel echt bestaan anders krijgen we een crash
				if(row < t1.length && row < t2.length) {
					//Als ze alle 2 bestaan de logische AND hiervan nemen
					if(colomn < t1[row].length && colomn < t2[row].length) {
						table[row][colomn] = t1[row][colomn] && t2[row][colomn];
					}
					//Anders is het zowiezo false, aangezien 1 van de 2 dan direct false is en false && * = false
					else
						table[row][colomn] = false;
				}
				else
					table[row][colomn] = false;
			}
		}

		return(table);
	}
	/*	                   			*\
	|Einde boolAnd functie 			 |
	\*   							*/



	/*	                   			*\
	|Begin boolOr functie 		 	 |
	\*                     			*/
	/**
	*Een functie die een kopie maakt van een boolean table maar met de logische Or toegepast op iedere waarde. Als de tabllen verschillend van lengte zijn gaan de missende waarden als false worden geinterpreteert
	*@param t1 Type: boolean[][] Doel: De linker tabel die geconverteerd moet worden, we verwachten een niet lege tabel.
	*@param t2 Type: boolean[][] Doel: De rechter tabel die geconverteerd moet worden, we verwachten een niet lege tabel. 
	*@return De geconverteerde tabel
	*/
	public static boolean[][] boolOr(boolean[][] t1, boolean[][] t2) {
		//teller
		int i;
		boolean [][]table;
		//input controle, als 1 van de 2 tabellen niet bestaat --> tabel terugsturen die wel bestaat aangezien we de logische or hebben klopt deze uitkomst
		if(t1.length < 1 && t2.length >= 1)
			return(t2);
		if(t2.length < 1 && t1.length >= 1)
			return(t1);
		//Kijken of tabel 1 en 2 een lengte hebben en hiervan de grootse pakken voor onze nieuwe tabel
		if(t1.length < 1 && t2.length >= 1) {
			table = new boolean[t2.length][];
			for(i = 0; i < t2.length; i++) {
				table[i] = new boolean[t2[i].length];
			}
		}
		if(t2.length < 1 && t1.length >= 1) {
			table = new boolean[t1.length][];
			for(i = 0; i < t1.length; i++) {
				table[i] = new boolean[t1[i].length];
			}
		}
		//Kolommen aanmaken op dezelfde manier als bij de boolAnd
		else {
			if(t1.length > t2.length)
				table = new boolean[t1.length][];
			else
				table = new boolean[t2.length][];
			for(i = 0; (i < t1.length || i < t2.length) && i < table.length; i++) {
				if(i >= t1.length)
					table[i] = new boolean[t2[i].length];
				if(i >= t2.length)
					table[i] = new boolean[t1[i].length];
				else {
					if(i < t1.length && i < t2.length && t1.length != 0 && t2.length != 0)
						if(t1[i].length > t2[i].length)
							table[i] = new boolean[t1[i].length];
						else
							table[i] = new boolean[t2[i].length];
					else {
						if(t1.length == 0 && i < t2.length)
							table[i] = new boolean[t2[i].length];
						else if(t2.length == 0 && i < t1.length)
							table[i] = new boolean[t1[i].length];
					}
				}	
			}
		
		}
		//Rijteller, kolomteller, teller
		int row, colomn;
		//Nieuwe tabel maken
		



		//tabel kopie gaan aanmaken gebasseerd op de grootse lengte van 1 v.d 2 tabellen voor zowel lengte als breedte
		


		//Elke rij en kolom afgaan om de nieuwe tabel een waarde te geven
		for(row = 0; row < table.length; row++) {
			for(colomn = 0; colomn < table[row].length; colomn++) {
				//Controleren of de rijen en kolommen wel bestaan ,zo ja de logische OF hiervan nemen, zo neen, kijken welke van de 2 wel bestaat op die plek en zijn waarde met de logisch OF false nemen
				if(row < t1.length && row < t2.length) {
					//zelfde principes als bij boolAnd, met als enigste verschil dat we hierbij false || * wel nog moeten uitrekenen
					if(colomn < t1[row].length && colomn < t2[row].length) {
						table[row][colomn] = t1[row][colomn] || t2[row][colomn];
					}
					else {
						if(colomn < t1[row].length && colomn >= t2[row].length)
							table[row][colomn] = (false || t1[row][colomn]);
						if(colomn < t2[row].length && colomn >= t1[row].length)
							table[row][colomn] = (false || t2[row][colomn]);
					}
				}
				else{
					if(row < t1.length && row >= t2.length) {
						if(colomn < t1[row].length) {
							table[row][colomn] = t1[row][colomn] || false;
						}
					}
					else if(row < t2.length && row >= t1.length) {
						if(colomn < t2[row].length) {
							table[row][colomn] = false || t2[row][colomn];
						}
					}
				}
			}
		}

		return(table);
	}
	/*	                   			*\
	|Einde boolOr functie 			 |
	\*   							*/




	/*	                   			*\
	|Begin findNumbers functie	 	 |
	\*                     			*/
	/**
	*Een functie die alle natuurlijke getallen uit een string haalt en deze in een array van integers stopt.
	*@param input Type: String Doel: De string die gecontroleerd moet worden op getallen
	*@return Een array met alle getallen in
	*/
	public static int[] findNumbers(String input) {
		int []table;
		int i,j, amountOfItems = 0;

		//aantal getallen in een string tellen voor zo de lengte van de tabel te kennen
		for(i = 0; i < input.length(); i++) {
			//Als hij een cijfer tegenkomt moet hij een interne teller starten
			if(input.charAt(i) >= '0' && input.charAt(i) <= '9') {
				//deze teller blijft loopen tot hij een niet cijfer tegenkomt
				while(i < input.length() && input.charAt(i) >= '0' && input.charAt(i) <= '9') {
					i++;
				}
				amountOfItems++;
			}
		}
		table = new int[amountOfItems];
		for(i = 0, amountOfItems = 0; i < input.length(); i++) {
			//Als hij een cijfer tegenkomt moet hij een interne teller starten
			if(input.charAt(i) >= '0' && input.charAt(i) <= '9') {
				//deze teller blijft loopen tot hij een niet cijfer tegenkomt
				j = i;
				while(j < input.length() && input.charAt(j) >= '0' && input.charAt(j) <= '9') {
					j++;
				}
				table[amountOfItems] = toDecimal(substring(input,i,j));
				amountOfItems++;
				i = j;
			}
		}
		return(table);
	}

	/**
	*Een functie die alle natuurlijke getallen uit een string haalt en deze in een array van integers stopt.
	*@param input Type: String Doel: De string die verdeeld gaat worden
	*@param left Type: int Doel: De startpositie voor onze substring, we gaan er van uit dat left < string.length() en we gaan er van uit dat dit een positief getal is
	*@param right Type: int Doel: De eindpositie voor onze substring (exclusief), we gaan er van uit dat right <= string.length() en we gaan er van uit dat dit een positief getal is
	*@return Een substring van input
	*/
	public static String substring(String input, int left, int right) {
		String newString = "";
		//Input controle
		if(left < 0)
			left *= -1;
		if(right < 0)
			right *= -1;
		//Zolang linker teller kleiner is als de rechter teller de letters blijven toevoegen aan de string
		while(left < right) {
			newString += input.charAt(left);
			left++;
		}
		return(newString);
	}

	/**
	*Een functie die alle natuurlijke getallen uit een string haalt en deze in een array van integers stopt.
	*@param input Type: String Doel: De string die omgezet gaat worden naar een int, we gaan er van uit dat onze input alleen cijfers bevat
	*@return De input string in getal vorm
	*/
	public static int toDecimal(String input) {
		int i, j, k, number = 0;
		int newInt = 0;
		//Elke digit in de string afgaan
		for(i = input.length() - 1; i >= 0; i--) {
			//String controle
			if(!(input.charAt(i) >= '0' && input.charAt(i) <= '9'))
				return(0);
			//Het getal omvormen naar een int
			number = (int)(input.charAt(i) - '0');
			//Aangezien de 5 in 500 dan '5' in een int zou zijn moeten me deze nog tot de juiste macht verheffen
			for(j = 1; j <= (input.length() - i) - 1; j++) {
				number *= 10;
			}
			//Dit getal dan bij de som optellen
			newInt += number;
		}

		return(number);
	}


	/*	                   			*\
	|Einde findNumbers functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin inBounds functie	 	 |
	\*                     			*/
	/**
	*Een functie die gaat controleren of die plaats bestaat in de matrix
	*@param table Type: boolean[][] Doel: De tabel die gechecked moet worden
	*@param i Type: int Doel: de rij plaats aanduiden, we gaan er van uit dat dit een positief getal is
	*@param j Type: int Doel: de kolom plaats aanduiden, we gaan er van uit dat dit een positief getal is
	*@return Een boolean die zegt of een op die plaats een cel bestaat
	*/
	public static boolean inBounds(boolean [][] table, int i, int j) {
		boolean exists;
		//input controle, negatieve plaatsen bestaan nooit
		if(i < 0|| j < 0)
			return(false);
		//Kijken of het aantal rijen kleiner is dan i, als dit waar is gaan we nog controleren of er een rij bestaat voor het geval van een lege tabel, zo ja kijken of de kolomlengte op die rij kleiner is dan j
		if (table.length > i && table.length >= 1 && table[i].length > j) {
			exists = true;
		}
		else {
			exists = false;
		}
		
		return(exists);
	}
	/*	                   			*\
	|Einde inBounds functie 		 |
	\*   							*/



	/*	                   			*\
	|Begin genBoolRow functie	 	 |
	\*                     			*/
	/**
	*Een functie die een boolean rij genereert
	*@param length Type: int Doel: de lengte van de rij aanduiden, we gaan er van uit dat dit een positief getal is
	*@return Een tabel van lengte (length) met willekeurig aantal true's
	*/
	public static boolean[] genBoolRow(int length) {
		//Nieuwe tabel aanmaken met lengte length
		boolean []table = new boolean[length];
		int i;
		//input controle
		if(length < 0)
			length *= -1;
		//Voor elke cel een willekeurig bepaalde booelan invullen
		for(i = 0; i < table.length; i++) {
			if((int)(Math.random() * 2) == 1)
				table[i] = true;
			else
				table[i] = false;
		}
		return(table);
	}
	/*	                   			*\
	|Einde genBoolRow functie 		 |
	\*   							*/


}