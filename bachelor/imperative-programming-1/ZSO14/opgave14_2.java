//opgave14_2.java

import tio.*;

class opgave14_2 {
	public static void main(String[] args) {
		int x = 4;
		int i;

		for(i = x - 1; i > 0 ; i--) {
			x += i;
		}
		System.out.println(x);
	}
}