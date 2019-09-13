import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.BoxLayout;
import java.awt.BorderLayout;
import javax.swing.JButton;
import java.awt.Button;
import java.awt.TextArea;
import java.io.*;

public class Test2 {
	
	
	public static PipedOutputStream pOut;
	private JFrame frame;
	public static TextArea textArea;
	static PipedInputStream pIn;  
	static BufferedReader reader;
	/**
	 * Launch the application.
	 */
	public static void start() {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Test2 window = new Test2();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Test2() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 * @throws IOException 
	 */
	private void initialize() throws IOException {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new BorderLayout(0, 0));
		
		Button button = new Button("New button");
		frame.getContentPane().add(button, BorderLayout.SOUTH);
		
		pOut = new PipedOutputStream();   
		pIn = new PipedInputStream(pOut);  
		reader = new BufferedReader(new InputStreamReader(pIn));
		
		textArea = new TextArea();
		frame.getContentPane().add(textArea, BorderLayout.CENTER);
		
		/*while(true) {
			try {
		        String line = reader.readLine();
		        if(line != null) {
		           	textArea.append(line);
		        }
		    } catch (IOException ex) {
		        // Handle ex
		    }
		}*/
		
	}
	
	public static void addcontent() {
		while(true) {
		try {
	        String line = reader.readLine();
	        if(line != null) {
	           	textArea.append(line);
	        }
	    } catch (IOException ex) {
	        // Handle ex
	    }
	}
	}

}
