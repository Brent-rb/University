//opgave12_10.java
import tio.*;

class opgave12_10 {
	public static void main(String[] args) {
		int table[] = new int [4];
		int i, input, getal, hulpgetal, j;
		System.out.println("Geef het aantal posities in");
		input = Console.in.readInt();
		if (input < 0) {
			input %= table.length;
			input += table.length;
		}
		else {
			input %= table.length;
		}
		for (i = 0; i < table.length ; i++) {
			table[i] = i;
			System.out.print(table[i]);
		}
		for (j = 0; j < input; j++) {
			hulpgetal = table[0];
			for (i = 0; i < table.length; i++) {
				if (i == table.length - 1) {
					table[0] = hulpgetal;
				}
				else {
					getal = hulpgetal;
					hulpgetal = table[i+1];
					table[i + 1] = getal;
				}
			}
		}
		System.out.println();
		for (i = 0; i < table.length; i++) {
			System.out.print("" + table[i] + " ");
		}
		System.out.println();	
	}
}