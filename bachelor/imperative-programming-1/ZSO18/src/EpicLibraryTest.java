//Doel: Het testen van andere functies

/**
*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
*/


class EpicLibraryTest {
	//Begin Main Functie, deze gaat alle methoden in dit bestand oproepen voor de functies van andere classes te testen.
	public static void main(String [] args) {
		boolean correct = true;
		//getRandom testen
		String succes = "*-------------------------------------*\n    Alle sub-tests zijn geslaagd!\n*-------------------------------------*";
		String fail = "*-----------------------------------------------*\n      Er zijn fouten opgetreden zie hierboven\n*-----------------------------------------------*";
		String unstoppable = "ۜ*---------------------------------*\n     Alle tests zijn geslaagd!\n*---------------------------------*";
		String fatality = "*-------------------------------------------------------*\n       Er zijn fouten opgetreden zie hierboven\n*-------------------------------------------------------*";
		//succes = "*-------------------------------------*\n Alle sub-tests zijn geslaagd! \\(^.^)/ \n*-------------------------------------*";
		//fail = "*-----------------------------------------------*\n Er zijn fouten opgetreden zie hierboven /(T.T)\\ \n*-----------------------------------------------*";
		//unstoppable = "ۜ*-----------------------------------------*\n (>^_^)> Alle tests zijn geslaagd! <(^_^<)\n*-----------------------------------------*";
		//fatality = "*-------------------------------------------------------*\n Er zijn fouten opgetreden zie hierboven (╯°□°）╯︵ ┻━┻  \n*-------------------------------------------------------*";
		System.out.println("Testen: getRandom()");
		if(test_getRandomAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//generateBoolTable testen
		System.out.println("Testen: generateBoolTable()");
		if(test_generateBoolTableAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//Convert2D -> 1D testen
		System.out.println("Testen: convertBool2D1D()");
		if(test_convertBool2D1DAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//FisherYate 1D testen
		System.out.println("Testen: shuffle1D()");
		if(test_shuffle1DAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		
		//FisherYate 2D Testen
		System.out.println("Testen: shuffle2D()");
		if(test_shuffle2DAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//CountTrue
		System.out.println("Testen: countTrue()");
		if(test_countTrueAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//countFalse
		System.out.println("Testen: countFalse()");
		if(test_countFalseAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//boolNot
		System.out.println("Testen: boolNot()");
		if(test_boolNotAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//boolAnd
		System.out.println("Testen: boolAnd()");
		if(test_boolAndAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//boolOr
		System.out.println("Testen: boolOr()");
		if(test_boolOrAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//findNumbers
		System.out.println("Testen: findNumbers()");
		if(test_findNumbersAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//inBounds
		System.out.println("Testen: inBounds()");
		if(test_inBoundsAll()){
			System.out.println(succes);
			correct &= true;
		}
		else{
			System.out.println(fail);
			correct = false;
		}
		//Einde tests

		if(correct) 
			System.out.println(unstoppable);
		else
			System.out.println(fatality);
	}

	/*	                   	*\
	|Begin test_getRandomAll |
	\*                     	*/
	
	/**
	*Een functie die de test_getRandom() functie oproept voor zo de getRandom() functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als alle tests geslaagd zijn anders geeft het een 'false' terug
	*/
	public static boolean test_getRandomAll() {
		boolean correct = true;
		//Basisgevallen
		correct = test_getRandom(0,1,true) && correct;
		//Einde Basisgevallen

		//Normale gevallen
		correct = test_getRandom(4,10,true) && correct;
		correct = test_getRandom(3,11,true) && correct;
		correct = test_getRandom(3,4,true) && correct;
		correct = test_getRandom(5,20,true) && correct;
		//Einde Normale gevallen

		//Randgevallen
		correct = test_getRandom(0,0,true) && correct;
		correct = test_getRandom(5,5,true) && correct;
		correct = test_getRandom(2,2,true) && correct;
		correct = test_getRandom(100,100,true) && correct;
		//Einde randgevallen

		//Grote invoer
		correct = test_getRandom(0,10000,true) && correct;
		correct = test_getRandom(5,200000,true) && correct;
		correct = test_getRandom(400000,400001,true) && correct;
		//Einde Grote invoer

		//Foute invoer
		correct = test_getRandom(1,0,false) && correct;
		correct = test_getRandom(5,0,false) && correct;
		correct = test_getRandom(200,0,false) && correct;
		correct = test_getRandom(4,3,false) && correct;
		correct = test_getRandom(-4,-3,false) && correct;
		//Einde foute invoer

		return(correct);
	}

	/**
	*Een functie die de getRandom() functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param under Type: int Doel: de ondergrens die we gaan testen
	*@Param above Type: int Doel: de bovengrens die we gaan testen
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_getRandom(int under, int above, boolean expected) {
		boolean correct;
		if(EpicLibrary.getRandom(under,above) <= above && EpicLibrary.getRandom(under,above) >= under)
			correct = true;
		else
			correct = false;
		if(correct == expected) {
			System.out.println("Test geslaagd voor input: [" + under + "," + above + "]");
		}
		else{	
			System.out.println("ERROR: Methode getRandom([" + under + "," + above + "])");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}
		return(correct == expected);
	}

	/**
	*Een functie die de test_generateBoolTable() functie gaat oproepen voor zo de generateBoolTable() functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_generateBoolTableAll() {
		boolean correct = true;
		//Basisgevallen
		correct = test_generateBoolTable(1,1,1,true) && correct;
		correct = test_generateBoolTable(2,2,1,true) && correct;
		correct = test_generateBoolTable(2,2,2,true) && correct;
		correct = test_generateBoolTable(2,2,3,true) && correct;
		correct = test_generateBoolTable(2,2,4,true) && correct;
		//Einde Basisgevallen

		//Normale gevallen
		correct = test_generateBoolTable(5,10,5,true) && correct;
		correct = test_generateBoolTable(3,11,5,true) && correct;
		correct = test_generateBoolTable(3,4,2,true) && correct;
		correct = test_generateBoolTable(5,20,10,true) && correct;
		//Einde Normale gevallen

		//Randgevallen
		correct = test_generateBoolTable(0,0,0,true) && correct;
		correct = test_generateBoolTable(5,5,25,true) && correct;
		correct = test_generateBoolTable(2,2,4,true) && correct;
		correct = test_generateBoolTable(100,100,10000,true) && correct;
		correct = test_generateBoolTable(-4,-3,11,false) && correct;
		correct = test_generateBoolTable(-3,-4,10,false) && correct;
		//Einde randgevallen

		//Grote invoer
		correct = test_generateBoolTable(10,10000,1000,true) && correct;
		correct = test_generateBoolTable(5,200000,50000,true) && correct;
		correct = test_generateBoolTable(40000,40000,50000,true) && correct;
		//Einde Grote invoer

		//Foute invoer
		correct = test_generateBoolTable(1,0,1,false) && correct;
		correct = test_generateBoolTable(5,0,1,false) && correct;
		correct = test_generateBoolTable(200,0,1,false) && correct;
		correct = test_generateBoolTable(4,3,17,false) && correct;
		correct = test_generateBoolTable(-4,-3,17,false) && correct;
		correct = test_generateBoolTable(-3,-4,17,false) && correct;
		//Einde foute invoer

		return(correct);
	}

	/**
	*Een functie die de generateBoolTable() functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param m Type: int Doel: Het aantal rijen specifieeren
	*@Param n Type: int Doel: Het aantal kolommen specifieeren
	*@Param t Type: int Doel: Het aantal cellen op true specifieeren
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_generateBoolTable(int m, int n, int t, boolean expected) {
		//Uitkomst boolean
		boolean correct = true;
		//Onze testtabel
		boolean [][]table = EpicLibrary.generateBoolTable(m,n,t);
		//Rijteller, Kolomteller, aantal true's teller
		int row, colomn, amountTrue = 0;

		//lengte en hoogte van tabel controleren
		//Rij lengte controleren
		if(m != table.length)
			correct = false;
		else
			correct = true;
		
		//Kolomn lengte controleren, we moeten enkel de kolom op de eerste rij testen aangezien het een rechthoekige matrix is
		if(table.length > 0 && n != table[0].length)
			correct = false;
		else{
			if(table.length == 0) {
				if(n == 0)
					correct = true;
				else
					correct = false;
			}
		}
		
		//Tabel afgaan voor aantal true's te tellen
		for(row = 0; row < table.length && correct; row++) {
			for(colomn = 0; colomn < table[row].length ; colomn++) {
				if(table[row][colomn] == true)
					amountTrue++;
			}
		}
		if(amountTrue == t)
			correct &= true;
		else
			correct = false;
		

		if(correct == expected) {
			System.out.println("Test geslaagd voor input: (" + m + "," + n + "," + t + ")");
		}
		else{	
			System.out.println("ERROR: Methode getRandom(" + m + "," + n + "," + t + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}
		return(correct == expected);
	}



	/**
	*Een functie die de test_convertBool2D1D functie gaat oproepen voor zo de convertBool2D1D functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_convertBool2D1DAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_convertBool2D1D(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_convertBool2D1D(temptable, true);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_convertBool2D1D(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_convertBool2D1D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_convertBool2D1D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_convertBool2D1D(temptable, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,5000);
		correct &= test_convertBool2D1D(temptable, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_convertBool2D1D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_convertBool2D1D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_convertBool2D1D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_convertBool2D1D(temptable, true);
		//Einde randgevallen
		return(correct);
	}


	/**
	*Een functie die de converBool2D1D functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: [][]boolean Doel: De tabel die we gaan converten
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_convertBool2D1D(boolean [][]table, boolean expected) {
		boolean correct = true;
		//nieuwe 1D tabel 
		boolean []newTable;
		//Tellers
		int i = 0, row,colomn;
		//De geconverteerde tabel in een nieuwe tabel opslagen
		newTable = EpicLibrary.convertBool2D1D(table);

		//Elke rij en kolom afgaan en vergelijken met de waarde van de rij, als correct = false stop hij 
		for(row = 0; row < table.length && correct; row++) {
			for(colomn = 0; colomn < table[row].length && correct; colomn++,i++) {
				if(table[row][colomn] != newTable[i])
					correct = false;
			}
		}

		//Uitprinten van resultaat met verwacht resultaat
		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode convertBool2D1D(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode convertBool2D1D(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}
		return(correct == expected);
	}


	/**
	*Een functie die de test_shuffle1D functie gaat oproepen voor zo de shuffle1D functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_shuffle1DAll() {
		boolean correct = true;

		//Basis input
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(1), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(2), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(3), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(4), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(5), true);
		//Normale input
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(10), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(15), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(20), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(30), true);
		//Grote input
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(300), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(450), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(489762), true);
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(346578), true);
		//rand gevallen
		correct &= test_shuffle1D(EpicLibrary.genBoolRow(0), true);



		return(correct);
	}


	/**
	*Een functie die de shuffle1D functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: Input die we moeten shuffelen
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_shuffle1D(boolean[] table, boolean expected) {
		boolean correct = true;
		//orginele aantal trues tellen
		int orginalTrues = EpicLibrary.countTrue(table);

		//Als de tabel < 39, visueel afdrukken (kan afhangen van grote letter & scherm etc...)
		//if(table.length <= 39)
		//	writeTable(table);

		//Tabel shuffelen
		EpicLibrary.shuffle1D(table);

		//if(table.length <= 39)
		//	writeTable(table);

		//Het aantal trues van de geshuffelde tabel vergelijken met de orginele aantal trues 
		if(EpicLibrary.countTrue(table) == orginalTrues)
			correct = true;
		else
			correct = false;

		if(correct == expected)
			System.out.println("Testcase geslaagd voor input: (" + table.length + ")");
		else {
			System.out.println("ERROR: Methode shuffle1D(" + table.length + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}

		return(correct == expected);
	}



	/**
	*Een functie die de test_shuffle1D functie gaat oproepen voor zo de shuffle1D functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_shuffle2DAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_shuffle2D(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_shuffle2D(temptable, true);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_shuffle2D(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_shuffle2D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_shuffle2D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_shuffle2D(temptable, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_shuffle2D(temptable, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_shuffle2D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_shuffle2D(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_shuffle2D(temptable, true);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_shuffle2D(temptable, true);



		return(correct);
	}


	/**
	*Een functie die de shuffle1D functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: Input die we moeten shuffelen
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_shuffle2D(boolean[][] table, boolean expected) {
		boolean correct = true;

		//Trues tellen van de orginele tabel
		int orginalTrues = EpicLibrary.countTrue(table);

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(table.length > 0 && table[0].length <= 39)
		//	writeTable(table);

		EpicLibrary.shuffle2D(table);

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(table.length > 0 && table[0].length <= 39)
		//	writeTable(table);

		//Het aantal trues vergelijken met het orginele aantal
		if(EpicLibrary.countTrue(table) == orginalTrues)
			correct = true;
		else
			correct = false;
		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode shuffle2D(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode shuffle2D(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}

		return(correct == expected);
	}


	/**
	*Een functie die de test_countTrue functie gaat oproepen voor zo de countTrue functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_countTrueAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_countTrue(temptable, 1);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_countTrue(temptable, 2);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_countTrue(temptable, 3);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_countTrue(temptable, 4);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_countTrue(temptable, 5);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_countTrue(temptable, 5);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_countTrue(temptable, 5);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_countTrue(temptable, 5);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_countTrue(temptable, 5);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_countTrue(temptable, 50);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_countTrue(temptable, 5000);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_countTrue(temptable, 500);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_countTrue(temptable, 100000);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_countTrue(temptable, 1);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_countTrue(temptable, 1);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_countTrue(temptable, 0);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_countTrue(temptable, 0);





		return(correct);
	}

	/**
	*Een functie die de countTrue functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: Input die we moeten controleren op true's
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_countTrue(boolean[][] table, int expected) {
		int amountTrue = EpicLibrary.countTrue(table);

		//Het aantal trues vergelijken met het orginele aantal
		if(amountTrue == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode countTrue(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode countTrue(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + amountTrue);
			System.out.println("Verwachte: " + expected);
		}

		return(amountTrue == expected);
	}



	/**
	*Een functie die de test_countFalse functie gaat oproepen voor zo de countFalse functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_countFalseAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_countFalse(temptable, 3);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_countFalse(temptable, 2);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_countFalse(temptable, 1);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_countFalse(temptable, 0);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_countFalse(temptable, 20);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_countFalse(temptable, 5);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_countFalse(temptable, 10);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_countFalse(temptable, 15);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_countFalse(temptable, 45);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_countFalse(temptable, 24999950);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_countFalse(temptable, 45000);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_countFalse(temptable, 9500);


		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_countFalse(temptable, 0);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_countFalse(temptable, 1);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_countFalse(temptable, 0);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_countFalse(temptable, 0);



		return(correct);
	}

	/**
	*Een functie die de countFalse functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: Input die we moeten controleren op false's
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_countFalse(boolean[][] table, int expected) {
		int amountFalse = EpicLibrary.countFalse(table);


		//Het aantal trues vergelijken met het orginele aantal
		if(amountFalse == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode countFalse(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode countFalse(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + amountFalse);
			System.out.println("Verwachte: " + expected);
		}

		return(amountFalse == expected);
	}


	/**
	*Een functie die de test_boolNot functie gaat oproepen voor zo de boolNot functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolNotAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_boolNot(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_boolNot(temptable, true);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_boolNot(temptable, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_boolNot(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_boolNot(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_boolNot(temptable, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_boolNot(temptable, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_boolNot(temptable, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_boolNot(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_boolNot(temptable, true);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_boolNot(temptable, true);



		return(correct);
	}


	/**
	*Een functie die de boolNot functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: Input die we gaan inverteren
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolNot(boolean[][] table, boolean expected) {
		boolean correct = true;
		boolean [][]newTable;

		//Trues tellen van de orginele tabel
		int orginalTrues = EpicLibrary.countTrue(table);

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(table.length > 0 &&  table.length < 50 && table[0].length <= 39)
		//	writeTable(table);
		
		//De functie uitvoeren die we moeten testen
		newTable = EpicLibrary.boolNot(table);

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(newTable.length > 0 && newTable.length < 50 && newTable[0].length <= 39)
		//	writeTable(newTable);

		//Het aantal false vergelijken met het orginele aantal trues aangezien deze functie alle waarden inverteerd
		if(EpicLibrary.countFalse(newTable) == orginalTrues)
			correct = true;
		else
			correct = false;
		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode boolNot(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode boolNot(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}

		return(correct == expected);
	}



	/**
	*Een functie die de test_boolAnd functie gaat oproepen voor zo de boolAnd functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolAndAll() {
		boolean correct = true;
		boolean [][]temptable;
		boolean [][]temptable2;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		temptable2 = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		temptable2 = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_boolAnd(temptable, temptable2, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		temptable2 = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		temptable2 = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_boolAnd(temptable, temptable2, true);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		temptable2 = EpicLibrary.generateBoolTable(5,5,4);
		correct &= test_boolAnd(temptable, temptable2, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		temptable2 = EpicLibrary.generateBoolTable(2,5,4);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		temptable2 = EpicLibrary.generateBoolTable(3,5,3);
		correct &= test_boolAnd(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		temptable2 = EpicLibrary.generateBoolTable(4,5,1);
		correct &= test_boolAnd(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		temptable2 = EpicLibrary.generateBoolTable(5,10,2);
		correct &= test_boolAnd(temptable, temptable2, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		temptable2 = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		temptable2 = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		temptable2 = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		temptable2 = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_boolAnd(temptable, temptable2, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		temptable2 = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_boolAnd(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		temptable2 = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_boolAnd(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		temptable2 = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		temptable2 = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,4,2);
		temptable2 = EpicLibrary.generateBoolTable(3,2,3);
		correct &= test_boolAnd(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(10,5,1);
		temptable2 = EpicLibrary.generateBoolTable(1,5,1);
		correct &= test_boolAnd(temptable, temptable2, true);



		return(correct);
	}


	/**
	*Een functie die de boolAnd functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: linker tabel voor de and vergelijking
	*@Param table2 Type: boolen[] Doel: rechter tabel voor de and vergelijking
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolAnd(boolean[][] table, boolean[][] table2, boolean expected) {
		boolean correct = true;
		boolean [][]newTable;
		int row, colomn;

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(table.length > 0 &&  table.length < 50 && table[0].length <= 39)
		//	writeTable(table);
		
		//De functie uitvoeren die we moeten testen
		newTable = EpicLibrary.boolAnd(table,table2);

		for(row = 0; row < newTable.length; row++) {
			for(colomn = 0; colomn < newTable[row].length; colomn++) {
				if(row < table.length && row < table2.length) {
					if(colomn < table[row].length && colomn < table2[row].length) {
						if(newTable[row][colomn] == (table[row][colomn] && table2[row][colomn]))
							correct = true;
						else
							correct = false;
					}
					else
						if(newTable[row][colomn] == false)
							correct = true;
						else
							correct = false;
				}
				else
					if(newTable[row][colomn] == false)
						correct = true;
					else
						correct = false;
			}
		}

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(newTable.length > 0 && newTable.length < 50 && newTable[0].length <= 39)
		//	writeTable(newTable);

		//Het aantal false vergelijken met het orginele aantal trues aangezien deze functie alle waarden inverteerd
		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode boolAnd(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode boolAnd(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}

		return(correct == expected);
	}


	/**
	*Een functie die de test_boolOr functie gaat oproepen voor zo de boolOr functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolOrAll() {
		boolean correct = true;
		boolean [][]temptable;
		boolean [][]temptable2;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		temptable2 = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		temptable2 = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_boolOr(temptable, temptable2, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		temptable2 = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		temptable2 = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_boolOr(temptable, temptable2, true);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		temptable2 = EpicLibrary.generateBoolTable(5,5,4);
		correct &= test_boolOr(temptable, temptable2, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		temptable2 = EpicLibrary.generateBoolTable(2,5,4);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		temptable2 = EpicLibrary.generateBoolTable(3,5,3);
		correct &= test_boolOr(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		temptable2 = EpicLibrary.generateBoolTable(4,5,1);
		correct &= test_boolOr(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		temptable2 = EpicLibrary.generateBoolTable(5,10,2);
		correct &= test_boolOr(temptable, temptable2, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		temptable2 = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		temptable2 = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		temptable2 = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		temptable2 = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_boolOr(temptable, temptable2, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		temptable2 = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_boolOr(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		temptable2 = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_boolOr(temptable, temptable2, true);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		temptable2 = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(0,0,1);
		temptable2 = EpicLibrary.generateBoolTable(0,0,1);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(2,4,2);
		temptable2 = EpicLibrary.generateBoolTable(3,2,3);
		correct &= test_boolOr(temptable, temptable2, true);

		temptable = EpicLibrary.generateBoolTable(10,5,1);
		temptable2 = EpicLibrary.generateBoolTable(1,5,1);
		correct &= test_boolOr(temptable, temptable2, true);



		return(correct);
	}


	/**
	*Een functie die de boolOr functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[] Doel: linker tabel voor de and vergelijking
	*@Param table2 Type: boolen[] Doel: rechter tabel voor de and vergelijking
	*@Param expected Type: boolean Doel: de uitkomst gaan controleren met de verwachte uitkomst
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_boolOr(boolean[][] table, boolean[][] table2, boolean expected) {
		boolean correct = true;
		boolean [][]newTable;
		int row, colomn;

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(table.length > 0 &&  table.length < 50 && table[0].length <= 39)
		//	writeTable(table);
		//if(table2.length > 0 &&  table2.length < 50 && table2[0].length <= 39)
		//	writeTable(table2);

		
		//De functie uitvoeren die we moeten testen
		newTable = EpicLibrary.boolOr(table,table2);

		if((EpicLibrary.countTrue(table) + EpicLibrary.countTrue(table2)) >= EpicLibrary.countTrue(newTable) && (EpicLibrary.countTrue(table) <= EpicLibrary.countTrue(newTable) || EpicLibrary.countTrue(table2) <= EpicLibrary.countTrue(newTable)))
			correct = true;
		else
			correct = false;

		//Als de tabel niet leeg is en kolom kleiner als 39 afdrukken (visueele controle);
		//if(newTable.length > 0 && newTable.length < 50 && newTable[0].length <= 39)
		//	writeTable(newTable);

		//Het aantal false vergelijken met het orginele aantal trues aangezien deze functie alle waarden inverteerd
		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode boolOr(" + table.length + "," + table[0].length + ")");
			else
				System.out.println("ERROR: Methode boolOr(" + table.length + "," + 0 + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}

		return(correct == expected);
	}





	/**
	*Een functie die de test_findNumbers functie gaat oproepen voor zo de findNumbers functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_findNumbersAll() {
		boolean correct = true;

		//Basis input
		correct &= test_findNumbers("100     200", 300);
		correct &= test_findNumbers("1 2 3 4 5 6 7 8 9", 45);
		correct &= test_findNumbers("1 2", 3);
		correct &= test_findNumbers("0   0", 0);
		//Normale input
		correct &= test_findNumbers("ab20 cd300,20,30   30, 50", 450);
		correct &= test_findNumbers("derpherp20derp30", 50);
		//Grote input
		correct &= test_findNumbers("jmldqfhisdmfhqds50dlfjqmdsk20ddjkqmsf30mjmàç)àç50", 150);
		correct &= test_findNumbers("jmldqfhisdmfhqds50dlfjqmdsk20ddjkqmsf30mjmàç)àç50jmldqfhisdmfhqds50dlfjqmdsk20ddjkqmsf30mjmàç)àç50jmldqfhisdmfhqds50dlfjqmdsk20ddjkqmsf30mjmàç)àç50jmldqfhisdmfhqds50dlfjqmdsk20ddjkqmsf30mjmàç)àç50", 600);
		//rand gevallen
		correct &= test_findNumbers("", 0);
		correct &= test_findNumbers("a", 0);



		return(correct);
	}

	/**
	*Een functie die de findNumbers functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param input Type: String Doel: de string waaruit we de getallen gaan inlezen
	*@Param expected Type: Int Doel: de som van de uitkomst tabel
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_findNumbers(String input, int expected) {
		int []outputTable = EpicLibrary.findNumbers(input);
		int i, sum = 0;
		boolean correct;

		//De som van de tabel nemen
		for(i = 0; i < outputTable.length; i++) {
			sum += outputTable[i];
		}

		if(sum == expected) {
			correct = true;
			System.out.println("Testcase geslaagd voor input: " + input);
		}
		else {
			correct = false;
			System.out.println("ERROR: Methode boolOr(" + input + ")");
			System.out.println("Gaf: " + sum);
			System.out.println("Verwachte: " + expected);
		}
		return(correct);

	}


	/**
	*Een functie die de test_inBounds functie gaat oproepen voor zo de inBounds functie te testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_inBoundsAll() {
		boolean correct = true;
		boolean [][]temptable;

		//Basisgevallen
		temptable = EpicLibrary.generateBoolTable(2,2,1);
		correct &= test_inBounds(temptable,1,1, true);

		temptable = EpicLibrary.generateBoolTable(2,2,2);
		correct &= test_inBounds(temptable,1,1, true);
	
		temptable = EpicLibrary.generateBoolTable(2,2,3);
		correct &= test_inBounds(temptable,1,1, true);

		temptable = EpicLibrary.generateBoolTable(2,2,4);
		correct &= test_inBounds(temptable,1,3, false);

		//Einde basisgevallen
		//Normale gevallen
		temptable = EpicLibrary.generateBoolTable(5,5,5);
		correct &= test_inBounds(temptable,4,4, true);
	
		temptable = EpicLibrary.generateBoolTable(2,5,5);
		correct &= test_inBounds(temptable,4,4, false);

		temptable = EpicLibrary.generateBoolTable(3,5,5);
		correct &= test_inBounds(temptable,4,5, false);
		
		temptable = EpicLibrary.generateBoolTable(4,5,5);
		correct &= test_inBounds(temptable,0,0, true);
		
		temptable = EpicLibrary.generateBoolTable(5,10,5);
		correct &= test_inBounds(temptable,4,5, true);
		//Einde normale gevallen
		//Grote input
		temptable = EpicLibrary.generateBoolTable(5000,5000,50);
		correct &= test_inBounds(temptable,4999,4999, true);

		temptable = EpicLibrary.generateBoolTable(5,10000,5000);
		correct &= test_inBounds(temptable,5,9999, false);

		temptable = EpicLibrary.generateBoolTable(1,10000,500);
		correct &= test_inBounds(temptable,0,9999, true);

		temptable = EpicLibrary.generateBoolTable(50000,10,100000);
		correct &= test_inBounds(temptable,500,2, true);

		//Einde grote input
		//Randgevallen
		temptable = EpicLibrary.generateBoolTable(1,1,1);
		correct &= test_inBounds(temptable,0,0, true);
		
		temptable = EpicLibrary.generateBoolTable(1,2,1);
		correct &= test_inBounds(temptable,1,2, false);
		
		temptable = EpicLibrary.generateBoolTable(0,2,1);
		correct &= test_inBounds(temptable,0,1, false);



		return(correct);
	}

	/**
	*Een functie die de inBounds functie gaat testen.
	*@Author Brent Berghmans 1334252 Bachelor 1 Informatica 2013-2014
	*@Param table Type: boolean[][] Doel: de input die we gaan testen
	*@Param row Type: int Doel: de rij v.d. cel die we gaan controleren (beginnend van 0)
	*@Param colomn Type: int Doel: de kolom v.d. cel die we gaan controleren (beginnende van 0)
	*@Param expected Type: boolean Doel: de uitkomst vergelijken
	*@Return Geeft een boolean terug die 'true' is als de test geslaagd is anders geeft het een 'false' terug
	*/
	public static boolean test_inBounds(boolean[][] table, int row, int colomn, boolean expected) {
		boolean correct;

		correct = EpicLibrary.inBounds(table, row, colomn);



		if(correct == expected) {
			if(table.length > 0)
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + table[0].length + ") met cel: (" + row + "," + colomn + ")");
			else
				System.out.println("Testcase geslaagd voor input: (" + table.length + "," + 0 + ") met cel: (" + row + "," + colomn + ")");
		}
		else {
			if(table.length > 0)
				System.out.println("ERROR: Methode inBounds(" + table.length + "," + table[0].length + ") met cel: (" + row + "," + colomn + ")");
			else
				System.out.println("ERROR: Methode inBounds(" + table.length + "," + 0 + ") met cel: (" + row + "," + colomn + ")");
			System.out.println("Gaf: " + correct);
			System.out.println("Verwachte: " + expected);
		}
		return(correct == expected);
	}






	/**
	*Een functie die een boolean tabel uittekent.
	*@Param table Type: boolean[][] Doel: De tabel die we gaan uitprinten
	*@Author Brent Berghmans 1334252 1ste Bachelor Informatica
	*/
	static void writeTable (boolean [][]table) {
		if(table.length == 0)
			return;
		int n1 = table.length;
		int n2 = table[0].length;
		int row, colomn, i = 0;
		
		for (row = 0; row < n1; row++) {
			for(i = 0; i < n2; i++) {
				if(row == 0) {
					if (i < n2)
						System.out.print(" _____");
					if (i == n2-1) {
						System.out.println();
					}
				}
			}
			for (i = 0; i < n2; i++) {
				if (i == 0)
					System.out.print("|     |");
				else
					System.out.print("     |");
			}
			System.out.println();
			for (colomn = 0; colomn < table[row].length; colomn++) {
				if (table[row][colomn]) {
					if(colomn != n2-1)
						System.out.print("|  T  ");
					else
						System.out.println("|  T  |");
				}
				else {
					if(colomn != n2-1)
						System.out.print("|  F  ");
					else
						System.out.println("|  F  |");
				}
			}
			for (i = 0; i < n2; i++) {
				if(i == 0)
					System.out.print("|_____|");
				else
					System.out.print("_____|");
			}
			System.out.println();
		}
	}
	/**
	*Een functie die een boolean rij uittekent.
	*@Param table Type: boolean[] Doel: De rij die we gaan uitprinten
	*@Author Brent Berghmans 1334252 1ste Bachelor Informatica
	*/
	static void writeTable(boolean []table) {
		if(table.length == 0)
			return;
		int i, j;
		
		for(i = 0; i < table.length; i++) {
			if (i == 0){
				for(j = 0; j < table.length; j++) {
					System.out.print(" _____");
				}
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j != table.length - 1)
						System.out.print("|     ");
					else
						System.out.println("|     |");
				}
			}
			if(i == 0)
				if(table[i])
					System.out.print("|  T  |");
				else
					System.out.print("|  F  |");
			else 
				if(table[i])
					System.out.print("  T  |");
				else
					System.out.print("  F  |");
			if (i == table.length - 1) {
				System.out.println();
				for(j = 0; j < table.length; j++) {
					if(j == 0)
						System.out.print("|_____|");
					else
						System.out.print("_____|");
				}
				System.out.println("\n");
			}
		}
	}
}