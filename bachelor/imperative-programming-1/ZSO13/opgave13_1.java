
class boo {
	public static void main (String[] args) {
		int[] a, b, c;

		a = new int[1];
		f1(a);
		System.out.println(a[0]);

		b = new int[1];
		f2(b);
		System.out.println(b[0]);

		c = f3();
		System.out.println(c[0]);
	}

	static void f1(int[] z) {
		z[0] = 29;
	}

	static void f2(int[] z) {
		z = new int[1];
		z[0] = 29;
	}

	static int[] f3() {
		int[] z = new int[1];
		z[0] = 29;
		return(z);
	}
}