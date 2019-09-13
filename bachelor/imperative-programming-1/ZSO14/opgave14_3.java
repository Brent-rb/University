import tio.*;

class opgave14_3 {
	public static void main(String [] args) {
		int product = 4, x = 4, y = 3;
		int i;

		for(i = 0 ; i < x; i++) {
			product *= product;
		}
		System.out.println("" + product);
	}
}