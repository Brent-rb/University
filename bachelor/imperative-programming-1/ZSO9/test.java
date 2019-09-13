import tio.*;

class test {
	public static void main(String[] args) {
		char c = 'c';
		int offset=5;
		c = (('z' - c) + ('a' - 1));
		c += offset;
		if (c + offset > 'z')
		    System.out.println("noob");
		System.out.println(c);
	}
}
		
