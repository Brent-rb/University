public class EetStokje{
	private static int $counter = 0;
	private int $nummer;
	
	public EetStokje(){
		$nummer = $counter++;
	}

	public String toString(){
		return "Stokje " + $nummer;
	}
}

