import tio.*;

class test {
    public static void main(String[] args) {
        int a = 100000;
        while (true) {
            if (((Math.random() * 3 * Math.random() * 100) < 100 ))
                System.out.print((char)((Math.random() * 9) + 48) + " ");
            else
                System.out.print((char)((Math.random() * 25) + 65) + " ");

        }
    }
}