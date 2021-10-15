package ece325_assignment2;

public class Song{
	private String title;
	
	/**
	 * Constructor for class will take the title of the song.
	 * @param title String that will define the name of the song.
	 */
	public Song(String title) {
		this.title = title;
	}
	/**
	 * Method to access the title outside of toString();
	 * @return title String The title of the song.
	 */
	public String getTitle() {
		return this.title;
	}
	
	/**
	 * String representation of Song class
	 * @return title String The title of the song
	 */
	public String toString() {
		return this.title;
	}
	
	@Override
	public boolean equals(Object obj) {
		// Test if we are comparing an object to its self.
		if (this == obj)
			return true;
		// If the object is null then it is not equal to anything.
		if (obj == null)
			return false;
		// If the object is not of class Song then it cannot be equal.
		if (getClass() != obj.getClass())
			return false;
		// Must cast the object to a Song in order to compare title.
		Song song = (Song) obj;
		// Compare based off the title. Case sensitive.
		return this.title.equals(song.toString());
	}
	
}