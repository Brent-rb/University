import tio.*;

class opgave14_10 {
	public static void main(String [] args) {
		int i, input, total;
		int [] table;
		System.out.println("Geef een getal in");
		input = Console.in.readInt();
		//Table de gewenste lengte geven
		table = new int [input];
		//Willekeurige getallen invullen
		table = randomTable(table);
		//De tabel printen
		writeTable(table);
		//De som berekenen
		total = add(table, input - 1);
		//De som vertonen
		System.out.println("De som is " + total);
	}

	//Random digit generator
	static int[] randomTable(int []table) {
		int i;

		for(i = 0; i < table.length; i++) {
			table[i] = (int)(Math.random() * 10);
		}

		return(table);
	}

	static void writeTable(int []table) {
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
				System.out.print("|  " + table[i] + "  |");
			else 
				System.out.print("  " + table[i] + "  |");
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

	static int add(int []table, int length) {
		int i;
		int total = 0;
		if (length % 2 == 0)
			length--;
		if(length > 0) {
			return (table[length] + add(table, length - 2)); 
		}
		if(length == 0)
			return(table[length]);
		return(total);
	}
}