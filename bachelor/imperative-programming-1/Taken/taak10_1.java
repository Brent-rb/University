//taak10_1.java

class taak10_1 {
	public static void main(String[] args) {
		String gegevenString, nieuweString = "";
		int i, k, letterGetal;
		int []a = new int [26];
		if (args.length < 1)
			return;
		gegevenString = args[0];
		for (i = 0; i < gegevenString.length(); i++) {
			letterGetal = (gegevenString.charAt(i) - 'a');
			a[letterGetal]++;
		}
		for (i = 0; i < a.length; i++) {
			letterGetal = a[i];
			for(k = 0; k < letterGetal; k++) {
				nieuweString += "" + (char)(i + 'a');
			}
		}
		System.out.println(nieuweString);
	}
}