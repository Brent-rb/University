//opgave15_4.java

import tio.*;

class opgave15_4 {
	public static void main(String[] args) {
	int max, size;
	System.out.println("Gimme max");
	max = Console.in.readInt();
	System.out.println("Gimme size");
	size = Console.in.readInt();

	writePart("", max, size);

	}

	static void writePart(String prefix, int max, int size) {
		int i;
		if(size != 0) {
			for(i = max; i >= size; i--) {
				if(size != 1)
					writePart(prefix + i + ",", i - 1, size - 1);
				else
					writePart(prefix + i, i - 1, size - 1);
			}
		}
		else {
			System.out.println(prefix);
			return;
		}
		return;
	}
}