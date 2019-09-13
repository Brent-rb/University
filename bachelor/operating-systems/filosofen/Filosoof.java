public class Filosoof extends Thread{
	private EetStokje $links, $rechts;
	private int $ikHeet;
	
	public Filosoof(int naam, EetStokje links, EetStokje rechts){
		$links  = links;
		$rechts = rechts;
		$ikHeet = naam;
		start();
	}

	public void denk(){
		try{
			sleep((int)Math.random() * 10);
		}catch(InterruptedException ie){
		}
	}


	public void eet(){
		System.out.println(this + " heeft honger");
		synchronized($links){
			try {
				sleep(1000);
			}
			catch(Exception e) {
				
			}
			System.out.println(this + " heeft " + $links.toString());
			synchronized($rechts){
				System.out.println(this + " heeft ook " + $rechts.toString() + "\n" +
				this + " kan eten nu!");
			}
		}
		System.out.println(this + " heeft genoeg");
	}

	public String toString(){
		return "Filosoof " + $ikHeet;
	}


	public void run(){
		while(true){
			denk();
			eet();
		}
	}
}


