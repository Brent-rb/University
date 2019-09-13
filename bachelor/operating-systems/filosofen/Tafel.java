import java.util.Vector;

public class Tafel{
	public Vector $filosofen;
	
	public Tafel(){
	}

	public void startMaal(int nrFil){
		$filosofen = new Vector();
		EetStokje links,rechts,eerst;
		links  = new EetStokje();
		rechts = new EetStokje();
		eerst = links;
		for(int i = 0; i<nrFil-1; i++){
			$filosofen.add(new Filosoof(i, links, rechts));
			links = rechts;
			rechts = new EetStokje();
		}
		$filosofen.add(new Filosoof(nrFil-1, links, eerst));	
	}
	
	public static void main(String args[]){
		Tafel t = new Tafel();
		t.startMaal(5);
	}
}
