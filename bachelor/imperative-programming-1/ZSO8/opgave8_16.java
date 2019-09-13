import tio.*;

class opgave8_16 {
    public static void main(String[] args) {
	int input, i, times = 0; 
	String givenString, newString, helpString;
	System.out.println("Geef een woord in");
	givenString = Console.in.readLine();
	System.out.println("1 : Verschuiven naar rechts");
	System.out.println("2 : Verschuiven naar links");
	System.out.println("3 : Verwisselen van 2 opeenvolgende letters");
	System.out.println("4 : Omkeren");
	System.out.println("5 : Letter toevoegen");
	System.out.println("6 : Letter verwijderen");
	System.out.println("7 : Willekeurig");
	do {
	    System.out.println("Geef een operatie in");
	    input = Console.in.readInt();
	    switch (input) {
	    case 1: givenString = right(givenString, times);
		System.out.println("De output is: " + givenString);
		break;
	    case 2: givenString = left(givenString, times);
		System.out.println("De output is: " + givenString);
		break;
	    case 3: givenString = turn(givenString);
		System.out.println("De output is: " + givenString);
		break;
	    case 4: givenString = backwards(givenString);
		System.out.println("De output is: " + givenString);
		break;
	    case 5: givenString = add(givenString);
		System.out.println("De output is: " +givenString);
		break;
	    case 6: givenString = delete(givenString);
		System.out.println("De output is: " + givenString);
		break;
	    case 7: givenString = random(givenString);
		System.out.println("De output is: " + givenString);
		break;
	    }
	} while(input != 0);
    }
    static String right(String givenString, int times){
	int length, i, i2;
	String newString="";
	if (times != 1) {
		System.out.println("Hoeveel posities ?");
		times = Console.in.readInt();
	}
	length = givenString.length() - 1;
	for (i2 = 1 ; i2 <= times ; i2++){
 	    newString = "";
	    newString += givenString.charAt(length);
	    for (i = 0; i < length ; i++){
		newString += givenString.charAt(i);
	    }
	    givenString = newString;
	}
	return(newString);
    }
    static String left(String givenString, int times){
	int length, i, i2;
	String newString="";
	length = givenString.length() -1;
	if (times != 1) {
		System.out.println("Hoeveel posities ?");
		times = Console.in.readInt();
	}
	for (i2 = 1; i2 <= times ; i2 ++){
	    newString = "";
	    for (i = 1; i <= length ; i++){
		newString += givenString.charAt(i);
	    }
	    newString += givenString.charAt(0);
	    givenString = newString;
	}
	return(newString);
    }
    static String turn(String givenString){
	int length, i;
	String newString = "";
	length = givenString.length() - 1;
	for (i = 0; (i + 1) <= length; i++) {
	    newString += givenString.charAt(i + 1);
	    newString += givenString.charAt(i);
	    i++;
	}
	if (i  == length)
	    newString += givenString.charAt(i);
	return(newString);
    }
    static String backwards(String givenString){
	int length, i;
	String newString = "";
	length = givenString.length() - 1;
	for (i = length; i >= 0; i--){
	    newString += givenString.charAt(i);
	}
	return(newString);
    }
    static String add(String givenString){
	String newString = "", inputString;
	System.out.println("Geef de letter/letters die je wilt toevoegen");
	inputString = Console.in.readLine();
	newString = givenString + inputString;
	return(newString);
    }
    static String delete(String givenString){
	int length, i, deleteChars;
	String newString = "";
	System.out.println("Hoeveel letters wil je verwijderen?");
	deleteChars = Console.in.readInt();
	length = givenString.length() - 1 - deleteChars;
	for(i = 0; i <= length; i++){
	    newString += givenString.charAt(i);
	}
	return(newString);
    }
    static String random(String givenString){
	int randomTimes, i, times = 1;
	String newString = "";
	for (i = 0; i <= 50; i++){
		randomTimes = (int)(Math.random() * 4.0 + 1.0);
		switch (randomTimes) {
			case 1: givenString = right(givenString, times);
				break;
	    		case 2: givenString = left(givenString, times);
				break;
	    		case 3: givenString = turn(givenString);
				break;
	    		case 4: givenString = backwards(givenString);
				break;
		}
	}
	return(givenString);
    }
}

	    
