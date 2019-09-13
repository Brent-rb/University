public class ThreadTest {

	public static void main(String[] args) {
		ThreadTest test = new ThreadTest();
		test.threadTest1(10);
		test.threadTest2(10);
		System.exit(0);
	}

	//Deze functie roept pas een volgende thread op als de vorige thread klaar is. (Iteratief)
	private void threadTest1(int numThreads) {
		Thread[] threads = new Thread[numThreads];
		for (int i = 0; i < threads.length; ++i) {
			threads[i] = new ThreadTest.MyThread();
			threads[i].start();
			try {
				threads[i].join();
			} catch (InterruptedException ie) { }
		}
	}

	//Deze functie roept alle thread in 1 keer op en wacht tot ze allemaal klaar zijn (kan in willekeurige volgorde gebeuren)
	private void threadTest2(int numThreads) {
		Thread[] threads = new Thread[numThreads];
		for (int i = 0; i < threads.length; ++i) {
			threads[i] = new ThreadTest.MyThread();
			threads[i].start();
		}
		for (int i = 0; i < threads.length; ++i)
		{
			try {
				threads[i].join();
			} catch (InterruptedException ie) { }
		}
	}

	class MyThread extends Thread {
		public void run() {
			try {
				sleep(1000);
			} catch (InterruptedException ie) { }
			System.out.println( getName() );
		}
	}
}