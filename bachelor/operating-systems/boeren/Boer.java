
public class Boer extends Thread {
	private Direction $dir;
	private Direction $riverDir;
	private int $pos;
	private Integer $lastPriority;
	private int $priority;
	private String $name;
	private static Integer $transits = 0;
	boolean $stop = false;

	public Boer(String name, Direction dir, Direction riverDir, Integer lastPrior) {
		$dir = dir;
		$riverDir = riverDir;
		$name = name;
		$lastPriority = lastPrior;
		$priority = 0;

		if($dir.isRight()) {
			$pos = 4;
		}
		else {
			$pos = 0;
		}
	}

	public void cross() {
		boolean crossed = false;
		synchronized($transits) {
			if($transits.intValue() > 1000000)
				$stop = true;
				
			synchronized($riverDir) {
				//System.out.println("Got RiverDir");
				//synchronized($lastPriority) {
					//System.out.println("Got LastPriority " + $lastPriority + ", my priority " + $priority);
					if($riverDir.differs($dir)) {
						if($dir.isLeft()) {
							while($pos != 4) {
								try {
									//sleep(1000);
									$pos++;
									//System.out.println("" + $name + " moved from rock " + ($pos - 1) + " to " + $pos + ".");
								}
								catch(Exception e) {
									//
								}
							}

							//System.out.println("" + $name + " reached the other side.");
							//System.out.println("" + $name + " " + $priority + " is tired from travel and will rest a bit.");
							$riverDir.set(Direction.Dir.LEFT);
							$dir.set(Direction.Dir.RIGHT);
							crossed = true;
							$priority++;
							$transits++;
						}
						else {
							while($pos != 0) {
								try {
									//sleep(1000);
									$pos--;
									//System.out.println("" + $name + " moved from rock " + ($pos + 1) + " to " + $pos + ".");
								}
								catch(Exception e) {
									//
								}
							}

							//System.out.println("" + $name + " reached the other side.");
							//System.out.println("" + $name + " " + $priority + " is tired from travel and will rest a bit.");
							$dir.set(Direction.Dir.LEFT);
							$riverDir.set(Direction.Dir.RIGHT);
							crossed = true;
							$priority++;
							$transits++;
						}
					}
				//}
			}
		}

		if(crossed) {
			try {
				//System.out.println("" + $name + " is tired from travel and will rest a bit.");
				//sleep(1);
			}
			catch(Exception e) {

			}
		}

	}

	public void run() {
		while(!$stop) {
			cross();
		}
		System.out.println("Boer " + $name + " walked " + $priority);
	}

	public int getPrior() {
		return $priority;
	}
}