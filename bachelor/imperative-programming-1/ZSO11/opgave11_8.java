//opgave11_8.java

class opgave11_8 {
	public static void main(String []args) {
		String string1, string2, substring = "", grootsteSubstring = "";
		char char1, char2, beginChar;
		int beginString1 = 0, beginString2, eindString1 = 0, eindString2 = 0, lengte = 0, j, i=0, hulpi; 
		string1 = args[0];
		string2 = args[1];
		char2 = string2.charAt(i);
		for (i = 0; i < string1.length(); i++){
			char1 = string1.charAt(i);
			hulpi = i;
			//zoekt eerstvolgende gelijke letter 
			for (j = 0; j < string2.length(); j++) {
				char1 = string1.charAt(hulpi);
				i = hulpi;
				while(j < string2.length() && char2 != char1) {
					char2 = string2.charAt(j);
					if (char1 == char2)
						break;
					j++;
				}
				//voegt ze toe aan een string zolang ze gelijk zijn
				while (i < string1.length() && j < string2.length() && char1 == char2) {
					char1 = string1.charAt(i);
					char2 = string2.charAt(j);
					if (char1 == char2){
						substring += "" + char1;
						i++;
						j++;
					}
				}
				System.out.println(j);
				System.out.println("De substring is " + substring);
				if (substring.length() > lengte) {
					lengte = substring.length();
					grootsteSubstring = substring;
				}
				substring = "";
				j --;
			}
			i = hulpi;

		}
		System.out.println("Grootste substring is " + grootsteSubstring);
		
	}
}