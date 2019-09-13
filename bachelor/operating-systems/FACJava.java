import java.io.*;
import java.util.*;

class FACJava implements Runnable {
	private int $fibbo;

	public FACJava(int fibbo) {
		$fibbo = fibbo;
	}

	public static void main(String[] args) {
		FACJava tempRunnable;
		Thread t;
		String input;
		int number;
		Scanner scanner = new Scanner(System.in);

		do {
			System.out.print("Enter a number:\n");
			input = scanner.nextLine();
			try {
				number = Integer.parseInt(input);
				if(number < 0)
					break;
				tempRunnable = new FACJava(number);
				t = new Thread(tempRunnable);
				t.start();
			} catch(Exception e) {
				System.out.println("Wrong input.");
			}
		} while(true);

	}

	public void run() {
		System.out.println("Fibbonacci of " + $fibbo + " is: " + fibbo($fibbo));
	}

	private int fibbo(int number) {
		if(number == 0)
			return 0;
		if(number == 1)
			return 1;

		else return fibbo(number - 1) + fibbo(number - 2);
	}
}

/*
Thread vs Runnable

Runnable is een interface dus kan men nog steeds van een klasse afleiden omdat in Java men meerdere interfaces kan implementeren maar maar van 1 klas kan afleiden.
Runnable geeft de klasse de mogelijkheid om op een andere thread te lopen, maar dit MOET niet. Wanneer men Thread extend zal men bij elk nieuw object een nieuwe thread aanmaken, dit is tevens ook heel zwaar.
*/