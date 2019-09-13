import tio.*;

class opgave14_11 {
	public static void main(String[] args) {
		String input;
		int length, i = 0;
		boolean isPalindroom;
		System.out.println("Geef een woord in");
		input = Console.in.readLine();
		length = input.length() - 1;

		isPalindroom = checkPalindroom(input, 0, length);
		
		System.out.print("" + input + " is ");
		if(isPalindroom)
			System.out.println("een palindroom");
		else
			System.out.println("geen palindroom");
	}


	static boolean checkPalindroom(String input, int begin, int end){
		boolean isPalindroom = false;
		if(begin != end) {
			isPalindroom = (input.charAt(begin) == input.charAt(end) && input.charAt(begin + 1) == input.charAt(end - 1));
		}
		return(isPalindroom);
	}
}