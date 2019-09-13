import tio.*;

class opgave13_3 {
	public static void main(String[] args) {
		int input[] = new int [6];
		boolean []generated = new boolean[42]; 
		boolean []inputTable = new boolean[42];
		int i, amount = 0, simAmount, n = 0, k;
		double profit = 0;
		simAmount = Console.in.readInt();
		while(profit <= 0){
			//for(k = 0; k < 3120; k++) {
				generated = genLotto();
				amount = 0;
				for(k = 0; k < simAmount; k++) {
					inputTable = genLotto();
					for (i = 0; i < generated.length; i++) {
						if ((generated[i] == true) && (inputTable[i] == true)) {
							amount++;
						}
					}
				}
				if(amount == 3)
					profit += 2.5;
				if(amount == 4)
					profit += 35;
				if(amount == 5)
					profit += 850;
				if(amount == 6)
					profit += 1000000;
			//}
			n++;
			profit -= (simAmount);
			System.out.println(profit);
		}
		System.out.println(n);

	}

	static boolean[] genLotto() {
		boolean []generated = new boolean [42];
		int i, amount = 0;
		int randomNum;
		while (amount != 6) {
			randomNum = (int)(Math.random() * 42.0);
			if (generated[randomNum] != true) {
				generated[randomNum] = true;
				amount++;
			}
		}
		return(generated);
	}
}