//opgave16_3.java

//Doel: Keer de tabel om
//Aanpak: zonder index: (0) <--> (table.length - 1), recursieve aanroep (table(1, table.length - 2));

import tio.*;

class opgave16_3 {
	public static void main(String [] args) {
		int []table;
		int index, length;

		System.out.println("Geef de lengte van de rij");
		length = Console.in.readInt();
		System.out.println("Geef de index");
		index = Console.in.readInt();
		table = new int[length];
		table = randomTable(table);
		writeTable(table);

		flipTable2(table, index);
		writeTable(table);

		flipTable1(table);
		writeTable(table);

	}

	static void flipTable1(int []table) {
		int i,j, hulp, length = table.length - 1;
		int []newTable;
		if(table.length <= 1)
			return;

		hulp = table[0];
		table[0] = table[length];
		table[length] = hulp;
		if(length - 2 >= 0)
			newTable = new int[length - 1];
		else
			return;
		for(i = 0; i < newTable.length; i++) {
			newTable[i] = table[i + 1];
		}
		flipTable1(newTable);

		for(i = 0; i < newTable.length ; i++) {
			table[i + 1] = newTable[i];
		}
		return;


	}


	static void flipTable2(int []table, int index) {
		int hulp, length = (table.length - 1) - index;
		if(index > length)
			return;
		hulp = table[index];
		table[index] = table[length];
		table[length] = hulp;
		flipTable2(table, index + 1);
		return;
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

	//Random digit generator
	static int[] randomTable(int []table) {
		int i;

		for(i = 0; i < table.length; i++) {
			table[i] = (int)(Math.random() * 10);
		}

		return(table);
	}

}