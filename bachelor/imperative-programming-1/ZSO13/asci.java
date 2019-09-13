//asci.java

class asci {
	public static void main(String[] args) {
		int i;
		for(i = -127; i <= 500; i++) {
			System.out.println("Ascii waarde: "+ i + " teken: " + ((char)i));
		}
	}
}