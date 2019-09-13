import tio.*;

class opgave17_2 {
	static long []fiboTable;
	public static void main(String [] args) {
		int input, n,i;
		
		long output, start, stop, delta;
		System.out.println("Geef het fibonacci getal dat je wilt");
		input = Console.in.readInt();
		
		//for(input = 10; input <= 50; input+= 10) {
		System.out.println("Input is : " + input);
		start = System.currentTimeMillis();
		output = fib(input - 1);
		stop = System.currentTimeMillis();
		delta = stop - start;
		System.out.println("De output van fib is " + output + " in: " + delta + "ms");

		start = System.currentTimeMillis();
		fiboTable = new long[input];
		for(i = 0; i < fiboTable.length; i++) {
			if(i == 0 || i == 1)
				fiboTable[i] = 1;
			else
				fiboTable[i] = fiboTable[i - 1] + fiboTable[i - 2];
		}
		output = fibArray(input - 1);
		stop = System.currentTimeMillis();
		delta = stop - start;


		System.out.println("De output van fibArray is " + output + " in: " + delta + "ms");
		start = System.currentTimeMillis();
		output = fibIt(input);
		stop = System.currentTimeMillis();
		delta = stop - start;

		System.out.println("De output van fibIt is " + output + " in: " + delta + "ms");
		//}

	}

	public static long fib(int input) {
		if(input == 0 || input == 1)
			return 1;
		else
			return(fib(input-1) + fib(input-2));
	}

	public static long fibArray(int input) {
		return(fiboTable[input]);
	}

	public static long fibIt(int input) {
		long number1 = 1, number2 = 1;
		int i;
		if(input == 0 || input == 1)
			return(number1);

		for(i = 2; i < input; i++) {
			if(i % 2 == 0)
				number1 = number1 + number2;
			else
				number2 = number1 + number2;
		}
		if(i % 2 != 0)
			return(number1);
		else
			return(number2);

	}
}