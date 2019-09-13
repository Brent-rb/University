
//UNIX
//Compile-Linux: 
//		javac -cp .:mp3agic-0.8.2-SNAPSHOT.jar:tio.jar:commons-io-2.4.jar YouNameIt.java
//Runnen-Linux:
//		java -cp .:mp3agic-0.8.2-SNAPSHOT.jar:tio.jar:commons-io-2.4.jar YouNameIt
//.Jar maken-Linux:
//		jar -cfm MusicEncoder.jar manifest.txt mp3agic-0.8.2-SNAPSHOT.jar tio.jar MusicEncoder.class MusicEncoder\$1.class
//Jar-runnen-Linux: 
// 		java -jar MusicEncoder.jar


//WINDOWS
//Compile-Windows
//		javac -cp .;mp3agic-0.8.2-SNAPSHOT.jar;tio.jar MusicEncoder.java
//Runnen-Windows
//		java -cp .;mp3agic-0.8.2-SNAPSHOT.jar;tio.jar MusicEncoder
//Jar-runnen-Windows: 
// 		java -jar MusicEncoder.jar

import tio.*;
import java.io.*;
import java.util.*;
import org.apache.commons.io.FileUtils;
import com.mpatric.mp3agic.ID3v1;
import com.mpatric.mp3agic.ID3v1Tag;
import com.mpatric.mp3agic.ID3v2;
import com.mpatric.mp3agic.ID3v24Tag;
import com.mpatric.mp3agic.InvalidDataException;
import com.mpatric.mp3agic.Mp3File;
import com.mpatric.mp3agic.NotSupportedException;
import com.mpatric.mp3agic.UnsupportedTagException;



//Pad: /home/brent/Documents/JavaOwnPrograms/Music\ Encoder/samples

class YouNameIt {
	static int i,j, succes = 0, fail = 0, skipped = 0;
	static File[] listOfFiles;
	
	
	public static void start(String pathname, String outputpath, boolean inverseMode, boolean writeAlbum, boolean selectMode, boolean skipMode, boolean forceMode){
		
		//String outputpath = "output/", pathname = "input";
		String fileArtist, fileTitle, filename, temp;
		String artist = "", title = "", album = "Derp", year = "", comment = "Made by UnamedIt", genre = "";
		boolean genreTrimMode = false;
		boolean []selection;
		
		List<File> listFiles; 
		listFiles = listf(pathname);
		listOfFiles = listFiles.toArray(new File[listFiles.size()]); 


		//Selection tabel initialiseren
		selection = new boolean[listOfFiles.length];
		
		Test2.start();
		System.setOut(new PrintStream(Test2.pOut));

		//quickSort(listOfFiles, 0, listOfFiles.length - 1);
		
		try{
			//Alle items in de lijst afgaan
			for(i = 0; i < listOfFiles.length; i++) {
				//Resets
				artist = "";
				title = "";


				filename = "" + listOfFiles[i];
				if(filename.charAt(filename.length() - 1) != '3' || filename.charAt(filename.length() - 2) != 'p' || filename.charAt(filename.length() - 3) != 'm' || filename.charAt(filename.length() - 4) != '.') {
					skipped++;
					continue;
					
				}

				//Als de selectie nee is
				if (selection[i])
					continue;

				//MP3File oproepen
				Mp3File mp3file;
				try {
					mp3file = new Mp3File("" + listOfFiles[i]);
				}catch(InvalidDataException e){
					System.out.println("Error: openen van " + listOfFiles[i].getName() + " is mislukt.");
					fail++;
					continue;
				}catch(IOException e) {
					System.out.println("Error: openen van " + listOfFiles[i].getName() + " is mislukt.");
					fail++;
					continue;
				}

				//Filename opvragen
				filename = listOfFiles[i].getName();

				//zoek naar het eerste - vanachter beginnende --> geeft aan wat de titel is en wat de artiest is 
				if(!inverseMode) {
					for (j = filename.length() - 1; j >= 0 && filename.charAt(j) != '-' ; j--);
					//Als er geen koppelteken gevonden is moet hij niks uitvoeren
					if(j > 1) {
						//title genereren en trimmen en eerste letter een hoofdletter maken (Stijlkeuze)
						title = filename.substring(j + 1, filename.length() - 4); // - 4 voor .mp3 weg te laten
						title = title.trim();
						title = capitalFirst(title);

						//De titel weglaten in de string met filename + filename
						filename = filename.substring(0, j);

						//artiest genereren en trimmen en eerste letter een hoofdletter maken (Stijlkeuze)
						artist = filename.substring(0, filename.length());
						artist = artist.trim();
						artist = capitalFirst(artist);

						//Als invers modus opstaat artiest = title & title = artiest
					}
					else {
						System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] Overgeslagen: Kan de artiest naam niet bepalen. Naam bestand: " + listOfFiles[i].getName());
						skipped++;
						continue;
					}
				}
				else {
					for (j = 0; j < filename.length() && filename.charAt(j) != '-' ; j++);
				//Als er geen koppelteken gevonden is moet hij niks uitvoeren
					if(j < filename.length()) {
						//title genereren en trimmen en eerste letter een hoofdletter maken (Stijlkeuze)
						title = filename.substring(0, j);
						title = title.trim();
						title = capitalFirst(title);

						//De titel weglaten in de string met filename + filename
						filename = filename.substring(j + 1);

						//artiest genereren en trimmen en eerste letter een hoofdletter maken (Stijlkeuze)
						artist = filename.substring(0, filename.length() - 4);
						artist = artist.trim();
						artist = capitalFirst(artist);

						//Als invers modus opstaat artiest = title & title = artiest
					}
					else {
						System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] Overgeslagen: Kan de artiest naam niet bepalen. Naam bestand: " + listOfFiles[i].getName());
						skipped++;
						continue;
					}

				}

				//Als het een tag heeft controleren of de tags niet leeg zijn 
				if (mp3file.hasId3v1Tag()) {
	   		    	ID3v1 id3v1Tag = mp3file.getId3v1Tag();
	   		    	fileArtist = "" + id3v1Tag.getArtist();
	   		    	fileTitle = "" + id3v1Tag.getTitle();

	   		    	//is de tag leeg, de gegenereerde tags in zetten
	   		    	if(fileArtist.length() != 0 && fileTitle.length() != 0 && !fileArtist.equals("null") && !fileTitle.equals("null")) {
	   		    		System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] Overgeslagen: heeft al een artiest en titel. Naam bestand: " + listOfFiles[i].getName());
	   		    		skipped++;
	   		    		continue;
	   		    	}
	   		    	else {
	   		    		id3v1Tag.setArtist(artist);
	   		    		id3v1Tag.setTitle(title);
	   		    		if(writeAlbum)
		   		    			id3v1Tag.setAlbum(album);
		   		    	id3v1Tag.setComment("Made By YouNameIt");
	   		    	}
	   		    }
 			    else {
 			    	if (mp3file.hasId3v2Tag()) {
		   		    	ID3v2 id3v2Tag = mp3file.getId3v2Tag();
		   		    	fileArtist = "" + id3v2Tag.getArtist();
		   		    	fileTitle = "" + id3v2Tag.getTitle();

		   		    	//is de tag leeg, de gegenereerde tags in zetten
		   		    	if(fileArtist.length() != 0 && fileTitle.length() != 0 && !fileArtist.equals("null") && !fileTitle.equals("null")) {
		   		    		System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] Overgeslagen: heeft al een artiest en titel. Naam bestand: " + listOfFiles[i].getName());
		   		    		skipped++;
		   		    		continue;
		   		    	}
		   		    	else {
		   		    		id3v2Tag.setArtist(artist);
		   		    		id3v2Tag.setTitle(title);
		   		    		if(writeAlbum)
		   		    			id3v2Tag.setAlbum(album);
		   		    		id3v2Tag.setComment("Made By YouNameIt");
		   		    	}
	   		    	}
	   		    	else {
	 			      	// mp3 does not have an ID3v1 tag, let's create one..
	 			      	ID3v1 id3v1Tag;
	 			      	id3v1Tag = new ID3v1Tag();
	 			      	mp3file.setId3v1Tag(id3v1Tag);
	 			      	id3v1Tag.setArtist(artist);
	 			      	id3v1Tag.setTitle(title);
	 			      	if(writeAlbum)
	 			      		id3v1Tag.setAlbum(album);
	 			      	id3v1Tag.setComment("Made By YouNameIt");
 			      	}
 			   	}
 			   	System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] " + listOfFiles[i] + " Wordt verwerkt.");
 			   	saveSong(mp3file, outputpath, i);

			}
 			
		}catch(Exception e){
			e.printStackTrace();
		}
		System.out.println("Aantal succesvol geconverteerd: [" + succes + "/" + listOfFiles.length + "]");
		System.out.println("Aantal gefaald: [" + fail + "/" + listOfFiles.length + "]");
		System.out.println("Aantal overgeslagen: [" + skipped + "/" + listOfFiles.length + "]");
		Test2.addcontent();
	}

	public static void saveSong(Mp3File mp3file, String outputpath, int i) {
		try	{
			if(i < listOfFiles.length)
	   			mp3file.save(outputpath + listOfFiles[i].getName());
	   		else
	   			return;
	   		System.out.println("Bestand [" + (i + 1) + "/" + listOfFiles.length + "] Succesvol opgeslagen op " + outputpath + listOfFiles[i].getName());
	   		succes++;
	   	}catch (NotSupportedException e) {
	   		System.out.println("Error: Opslagen van " + listOfFiles[i].getName() + " is mislukt.");
	   	   	fail++;
	  	   	return;
	   	}
	    catch (IOException e) {
	   		System.out.println("Error: Opslagen van " + listOfFiles[i].getName() + " is mislukt.");
	   		fail++;
	   		return;
	   	}
	   	catch (ArrayIndexOutOfBoundsException e) {
	   		System.out.println("Error: Opslagen van " + listOfFiles[i].getName() + " is mislukt.");
	   		fail++;
	   		return;
	   	}
	}

	public static List<File> listf(String directoryName) {
        File directory = new File(directoryName);

        List<File> resultList = new ArrayList<File>();

        // get all the files from a directory
        File[] fList = directory.listFiles();
        resultList.addAll(Arrays.asList(fList));
        for (File file : fList) {
            if (file.isFile()) {
                System.out.println("File gevonden: " + file.getAbsolutePath());
                
            } else if (file.isDirectory()) {
                resultList.addAll(listf(file.getAbsolutePath()));
            }
        }
        //System.out.println(fList);
        return resultList;
    }

	static String capitalFirst(String input) {
		String newString = "";
		int i;
		if(input.charAt(0) >= 'a' && input.charAt(0) <= 'z') {
			newString = "" + (char)((input.charAt(0) - 'a') + 'A');
		}
		else
			newString += input.charAt(0);

		for(i = 1; i < input.length(); i++) {
			newString += input.charAt(i);
			if(input.charAt(i) == ' ') {
				if(input.charAt(i + 1) >= 'a' && input.charAt(i + 1) <= 'z') {
					newString += (char)((input.charAt(i) - 'a') + 'A');
					i++;
				}
			}
		}
		return(newString);
	}	
}

