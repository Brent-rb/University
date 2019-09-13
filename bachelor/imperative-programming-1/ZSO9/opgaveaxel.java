class opgaveaxel {
	public static void main(String[] args) {
		String gegevenString;
		int i = 0, hoogsteGetal=0, kleinsteGetal=9, c;
		if (args.length != 1) 
			return;
		gegevenString = args[0];
		if (gegevenString.length() == 0)
			return;
		while (i < gegevenString.length()) {
			c = (int)gegevenString.charAt(i);
			if ((c >= '0' && c <= '9'))
				c -= '0';
			if (c > hoogsteGetal)
				hoogsteGetal = c;
			if (c < kleinsteGetal)
				kleinsteGetal = c;
		i++;
		}
		System.out.println("Het grootste getal is: " + hoogsteGetal);
		System.out.println("Het kleinste getal is: " + kleinsteGetal);
	}
}			
					
