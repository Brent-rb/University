
public class Rivier extends Thread {
	private Direction $dir;
	private Integer $lastPriority;

	public Rivier() {
		$dir = new Direction(Direction.Dir.LEFT);
		$lastPriority = new Integer(0);
	}

	public static void main(String[] args) {
		Rivier river = new Rivier();

		river.start();
	}

	public void run() {
		Boer jeff = new Boer("Jeff", new Direction(Direction.Dir.LEFT), $dir, $lastPriority);
		Boer tom = new Boer("Tom", new Direction(Direction.Dir.RIGHT), $dir, $lastPriority);
		Boer frank = new Boer("Frank", new Direction(Direction.Dir.LEFT), $dir, $lastPriority);
		Boer drollie = new Boer("Drollie", new Direction(Direction.Dir.LEFT), $dir, $lastPriority);
		Boer axel = new Boer("Axel", new Direction(Direction.Dir.RIGHT), $dir, $lastPriority);
		Boer matthijs = new Boer("Matthijs", new Direction(Direction.Dir.RIGHT), $dir, $lastPriority);

		jeff.start();
		tom.start();
		frank.start();
		drollie.start();
		axel.start();
		matthijs.start();

		while(true); /* {
			boolean synced = false;
			synchronized($lastPriority) {
				$lastPriority = jeff.getPrior();
				if($lastPriority > tom.getPrior())
					$lastPriority = tom.getPrior();
				if($lastPriority > frank.getPrior())
					$lastPriority = frank.getPrior();
				if($lastPriority > drollie.getPrior())
					$lastPriority = drollie.getPrior();
				if($lastPriority > axel.getPrior())
					$lastPriority = axel.getPrior();
				if($lastPriority > matthijs.getPrior())
					$lastPriority = matthijs.getPrior();

				System.out.println("lastPriority " + $lastPriority);

				synced = true;
			}
			if(synced) {
				try {
					sleep(2000);
				}
				catch(Exception e) {
					//
				}
			}
		}*/
	}
}