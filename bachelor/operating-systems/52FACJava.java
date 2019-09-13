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
			System.out.print("Enter a number: ");
			input = scanner.nextLine();
			number = Integer.parseInt(input);
			tempRunnable = new FACJava(number);
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