import tio.*;

class opgave8_13 {
	public static void main(String[] args) {
		String gegevenString, nieuweString = "";
		char hulpletter;
		int i, offset, keuze;
		System.out.println("Geef een string in");
		gegevenString = Console.in.readLine();
		System.out.println("Geef een offset in");
		offset = Console.in.readInt();
		System.out.println("Maak een keuze: 1: encodeer, 2: decodeer");
		keuze = Console.in.readInt();
		switch (keuze) {
			case 1: encoderen(gegevenString, offset);
				break;
			case 2: decoderen(gegevenString, offset);
				break;
		}
	}
	static void encoderen (String gegevenString, int offset) {
		int i;
		String nieuweString = "";
		char hulpletter;
		for (i = 0; i < gegevenString.length(); i++) {
			hulpletter = gegevenString.charAt(i);
			if(hulpletter <= 'z' && hulpletter >= 'a') {
				if (hulpletter + offset > 'z')
					hulpletter = (char)((offset - ('z' - hulpletter)) + ('a' - 1));
				else
					hulpletter += offset;
			}
			nieuweString += "" + hulpletter;
		}
		System.out.println(nieuweString);
	}
	static void decoderen (String gegevenString, int offset) {
		int i;
		String nieuweString = "";
		char hulpletter;
		for (i = 0; i < gegevenString.length(); i++) {
			hulpletter = gegevenString.charAt(i);
			if (hulpletter <= 'z' && hulpletter >= 'a') {
				if (hulpletter - offset < 'a')
					hulpletter = (char)(('z' + 1) - (offset - (hulpletter - 'a')));  
				else
					hulpletter -= offset;
			}
			nieuweString += "" + hulpletter;
		}
		System.out.println(nieuweString);
	}
}
