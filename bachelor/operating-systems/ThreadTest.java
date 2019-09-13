public class ThreadTest {

	public static void main(String[] args) {
		ThreadTest test = new ThreadTest();
		//test.threadTest1(10);
		test.threadTest2(10);
		System.exit(0);
	}

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