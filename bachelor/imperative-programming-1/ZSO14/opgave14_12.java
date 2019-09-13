import tio.*;

class opgave14_12 {
	public static void main(String[] args) {
		String input;
		int output, length;

		System.out.println("Geef een string van getallen in");
		input = Console.in.readLine();
		length = input.length() - 1;
		output = turnInt(input, length);
		System.out.println("De uitkomst is " + output);
	}

	static int turnInt(String input, int i) {
		
		int digit,j = i, output = 0;
		if(i >= 0) {
			digit = (int)(input.charAt(i) - '0');
			while(j < input.length() - 1){
				digit *= 10;
				j++;
			}
			output = digit + turnInt(input, i - 1);
		}
		else
			return(0);
		return(output);
	}
}