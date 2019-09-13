//opgave15_5.java

import tio.*;

class opgave15_5 {
	public static void main(String[] args) {
		int input, index = 0;
		System.out.println("Gimme N");
		input = Console.in.readInt();
		writeSumTable("",0, input, input);
	}

	static void writeSumTable(String answerString,int sumPrev, int input, int index) {
		int i;
		if(index >= 1) {
			for(i = index; i >= 1; i--) {
				if(sumPrev + i < input){
					writeSumTable(answerString + i + ",", sumPrev + i, input, i);
				}
				if(sumPrev + i == input)
					System.out.println(answerString + i);
			}
		}
		else 
			return;
		return;
	}
}