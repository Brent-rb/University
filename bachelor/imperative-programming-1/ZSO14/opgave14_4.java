import tio.*;

class opgave14_4 {
	public static void main(String [] args) {
		String s = "abcd";
		int pos = s.length() - 1;
		int i;

		for(i = pos; i >= 0 ; i--) {
			System.out.print(s.charAt(i));
		}
		System.out.println();
	}
}