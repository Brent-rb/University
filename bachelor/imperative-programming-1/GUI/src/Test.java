import java.awt.EventQueue;

import javax.swing.JFrame;
import java.awt.GridLayout;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.layout.RowSpec;
import com.jgoodies.forms.factories.FormFactory;

import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.Label;
import javax.swing.JLabel;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.Checkbox;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.TextField;
import javax.swing.JCheckBox;


public class Test {

	private JFrame frame;
	private TextField textField;
	private Label label;
	private Label lblNewLabel;
	private TextField textField_1;
	private Checkbox checkbox;
	private Checkbox checkbox_1;
	private Checkbox checkbox_2;
	private JButton btnNext;
	JFileChooser chooser;
	String choosertitle;
	boolean inverseMode = false;
	boolean albumMode = false;
	boolean selectMode = false;
	boolean skipMode = false;
	boolean forceMode = false;
	public static String inputdirectory = "";
	public static String outputdirectory = "";
	private Label lblNewLabel_1;
	private TextField textField_2;
	private Checkbox checkbox_3;
	private Checkbox checkbox_4;
	private directorychooser btnDirectory;
	private directorychooser2 btnChooseDirectory;
	private static Test window;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					window = new Test();
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
	public Test() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 415);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new FormLayout(new ColumnSpec[] {
				FormFactory.RELATED_GAP_COLSPEC,
				FormFactory.DEFAULT_COLSPEC,
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("default:grow"),
				FormFactory.RELATED_GAP_COLSPEC,
				FormFactory.DEFAULT_COLSPEC,
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("default:grow"),},
			new RowSpec[] {
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,
				FormFactory.RELATED_GAP_ROWSPEC,
				FormFactory.DEFAULT_ROWSPEC,}));
		
		label = new Label("Choose input directory");
		label.setFont(new Font("Droid Sans", Font.BOLD, 13));
		frame.getContentPane().add(label, "4, 2");
		
		textField = new TextField();
		textField.setEditable(false);
		frame.getContentPane().add(textField, "4, 4, fill, center");
		textField.setColumns(20);
		textField.setText(inputdirectory);
		
		btnDirectory = new directorychooser();
		btnDirectory.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				JFrame frame = new JFrame("");
			    directorychooser panel = new directorychooser();
			    frame.addWindowListener(
			      new WindowAdapter() {
			        public void windowClosing(WindowEvent e) {
			          System.exit(0);
			          }
			        }
			      );
			    frame.setSize(panel.getPreferredSize());
			    frame.setVisible(true);
			}
		});
		
		frame.getContentPane().add(btnDirectory, "6, 4, default, bottom");
		
		lblNewLabel = new Label("Choose output directory");
		lblNewLabel.setFont(new Font("Droid Sans", Font.BOLD, 13));
		frame.getContentPane().add(lblNewLabel, "4, 6");
		
		textField_1 = new TextField();
		textField_1.setEditable(false);
		frame.getContentPane().add(textField_1, "4, 8, fill, center");
		textField_1.setColumns(10);
		textField_1.setText(outputdirectory);
		
		btnChooseDirectory = new directorychooser2();
		btnChooseDirectory.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				JFrame frame = new JFrame("");
			    directorychooser2 panel = new directorychooser2();
			    frame.addWindowListener(
			      new WindowAdapter() {
			        public void windowClosing(WindowEvent e) {
			          System.exit(0);
			          textField_1.setText(outputdirectory);
			
			          }
			        
			        }
			      );
			    frame.setSize(panel.getPreferredSize());
			    frame.setVisible(false);
			}
		});

		frame.getContentPane().add(btnChooseDirectory, "6, 8, default, bottom");
		
		checkbox = new Checkbox("Inverse Mode");
		checkbox.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				inverseMode = !inverseMode;
			}
		});
		frame.getContentPane().add(checkbox, "4, 10");
		
		checkbox_1 = new Checkbox("Custom Album");
		checkbox_1.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				albumMode = !albumMode;
				textField_2.setEnabled(albumMode);
			}
		});
		frame.getContentPane().add(checkbox_1, "4, 12");
		
		checkbox_2 = new Checkbox("Selection?");
		checkbox_2.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				selectMode = !selectMode;
			}
		});
		
		lblNewLabel_1 = new Label("Album Name");
		frame.getContentPane().add(lblNewLabel_1, "6, 12");
		
		textField_2 = new TextField();
		textField_2.setEnabled(false);
		frame.getContentPane().add(textField_2, "6, 14");
		frame.getContentPane().add(checkbox_2, "4, 16");
		
		checkbox_3 = new Checkbox("Skip Mode?");
		checkbox_3.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent arg0) {
				skipMode = !skipMode;
			}
		});
		frame.getContentPane().add(checkbox_3, "4, 18");
		
		checkbox_4 = new Checkbox("Force Mode?");
		checkbox_4.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
			forceMode = !forceMode;
			}
		});
		frame.getContentPane().add(checkbox_4, "4, 20");
		
		
		btnNext = new JButton("Next");
		btnNext.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				window.frame.setVisible(false);
				YouNameIt.start(inputdirectory, outputdirectory, inverseMode, albumMode, selectMode, skipMode, forceMode);
			}
		});
		frame.getContentPane().add(btnNext, "6, 24");
		
	}
	
}
