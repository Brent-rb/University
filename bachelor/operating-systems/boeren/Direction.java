
public class Direction {
	private String $dir;
	public static enum Dir {LEFT, RIGHT};

	public Direction(Dir dir) {
		if(dir == Dir.LEFT) 
			$dir = "left";
		if(dir == Dir.RIGHT)
			$dir = "right";
	}

	public boolean equals(Direction dir) {
		return dir.$dir == this.$dir;
	}

	public boolean differs(Direction dir) {
		return !equals(dir);
	}

	public boolean isLeft() {
		return $dir == "left";
	}

	public boolean isRight() {
		return $dir == "right";
	}

	public void set(Dir dir) {
		if(dir == Dir.LEFT)
			$dir = "left";
		else
			$dir = "right";
	}

	public Dir get() {
		if($dir == "left")
			return Dir.LEFT;
		else
			return Dir.RIGHT;
	}
}