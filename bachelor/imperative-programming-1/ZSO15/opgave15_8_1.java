//opgave15_4.java

import tio.*;

class opgave15_8_1 {
	public static void main(String[] args) {
	int length;
	char []alfabet = new char[4];
	alfabet[0] = 'A';
	alfabet[1] = 'C';
	alfabet[2] = 'T';
	alfabet[3] = 'G';
	System.out.println("Gimme the length");
	length = Console.in.readInt();

	writeAll("", length, alfabet);

	}

	static void writeAll(String answerString, int index, char[] alfabet) {
		int i;

		if(index > 0) {
			for(i = 0; i < alfabet.length; i++) {
				writeAll(answerString + alfabet[i], index - 1, alfabet);
			}
		}
		else{
			System.out.println(answerString);
			return;
		}
		return;
	}
}
