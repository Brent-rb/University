import java.io.*;
import java.util.*;

class 52FACJava implements Runnable {
	private int $fibbo;

	public 52FACJava(int fibbo) {
		$fibbo = fibbo;
	}

	public static void main(String[] args) {
		52FACJava tempRunnable;
		Thread t;
		String input;
		int number;
		Scanner scanner = new Scanner(System.in);

		do {
			System.out.print("Enter a number: ");
			input = scanner.nextLine();
			try {
				number = Integer.parseInt(input);
			catch(Exception e) {
				System.out.println("Wrong input.");
			}
			tempRunnable = new 52FACJava(number);
			t = new Thread(tempRunnable);
			t.start();
		}

	}

	public void run() {
		fibbo($fibbo);
	}

	private void fibbo(int number) {
		if(number == 0)
			return 0;
		if(number == 1)
			return 1;

		else return fibbo(number - 1) + fibbo(number - 2);
	}
}