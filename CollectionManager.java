package ece325_assignment2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class CollectionManager {
	
	/**
	 * CollectionManager is designed to load song names in from a text file then create an
	 * Album object using those Strings.
	 * @param args
	 */
	public static void main(String[] args) {
		// Load all the songs given in the songs.txt into a String array
		String[] songNames = null;
		// LoadSongs has been alerted in a form that it may throw an exception so
		// we surround the call with a try/catch
		// http://pages.cs.wisc.edu/~deppeler/cs367-common/readings/Exceptions/
		try {
			songNames = loadSongs("songs.txt");
		}catch(Exception e) {
			System.out.println("There was an error in creating the String array 'songNames");
			e.printStackTrace();
		}
		// LoadSongs returns null if something goes wrong with loading the text.
		if(songNames != null) {
			Song[] songs = new Song[songNames.length];
			for(int i = 0; i < songNames.length; i++) {
				// Populate the songs array that will contain all songs in the text file.
				songs[i] = new Song(songNames[i]);
			}
			// Create the biggest album possible (no repeated songs)
			Album bigAlbum = new Album(songs);
			System.out.println(bigAlbum);
		}
		
	}
	
	/**
	 * Load strings line by line from a text file and put into a String array.
	 * 
	 * @param file String of the text file name
	 * @return songs which is the string array of all the songs in text file.
	 * @return null if there was an exception thrown in reading the file.
	 */
	private static String[] loadSongs(String file) throws IOException{
		// Define songs as a size 0 array to make the compiler smile.
		String[] songs = new String[0];
		// Must initialize BufferedReader in order to close in the finally statement.
		BufferedReader input = null;
		try {
			// Create a new reader from the file string given.
			input = new BufferedReader(new FileReader(file));
			String line;
			int i = 0;
			// First line of file will contain an integer with the amount of songs to be read.
			int totalLines = Integer.parseInt(input.readLine());
			// Array to be returned.
			songs = new String[totalLines];
			// BufferedReader will read line by line in the text file
			while((line = input.readLine()) != null) {
				songs[i] = line;
				i++;
			}
		
			return songs;
		}catch (Exception e) {
			System.err.println("Could not read song for the file " + file);
			e.printStackTrace();
			return null;
		} finally {
			// Close the BufferedReader if it was opened properly.
			if(input != null)
				input.close();
		}
	}
	
}
