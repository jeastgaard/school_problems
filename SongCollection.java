package ece325_assignment2;

import java.util.ArrayList;

/** 
 * This is a collection of all songs of your band. 
 * YOU ARE NOT ALLOWED TO MAKE CHANGES TO THIS CLASS.
 * @author corpaul
 *
 */
public class SongCollection {
	private ArrayList<Song> collection;
	
	public SongCollection() {
		collection = new ArrayList<Song>();
	}
	
	public void addSongToCollection(Song s) {
		collection.add(s);
	}
	
	public int getNumberOfSongs() {
		return collection.size();	}
	
	protected boolean contains(Song s) {
		return collection.contains(s);
	}
	
	
	public String toString() {
		String str = "[SongCollection: \n";
		for(Song s : collection)
			str += "\t" + s.getTitle() + "\n";
		str += "]";
		return str;
	}
	

}