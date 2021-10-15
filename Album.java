package ece325_assignment2;

public class Album{
	private Song[] songList; // Contains all the songs available
	private SongCollection albumSongs;  // Hold the songs that can go on the album
	private String albumString;  // String that will represent the Album object
		
		/**
		 * Contructor which requires a array of Songs
		 * @param songList Song[] will hold all the songs being requested to be put in the album.
		 */
		public Album(Song[] songList) {
			// We do not need to create a clone since we are not altering the array.
			this.songList = songList;
			// Initialize string
			this.albumString = "";
			// Create album using the SongCollection class
			this.createAlbum();
		}
		
		/**
		 * Will create the SongCollection that will represent the album.
		 */
		private void createAlbum() {
			int count = 0;
			albumSongs = new SongCollection();
			for(Song s : songList) {
				// If the song is not already in the collection then we can add it.
				if(!albumSongs.contains(s)) {
					count++;
					// Update the object string every time we add a new song
					this.albumString = this.albumString + "Track #" + Integer.toString(count) + ": " + s.toString() + "\n";
					albumSongs.addSongToCollection(s);
				}
			}
		}
		/**
		 * Gets the Album Size
		 * @return number of songs represented by the ArryList<Song> size in the collection object.
		 */
		public int getAlbumSize() {
			return albumSongs.getNumberOfSongs();
		}
		
		public String colllectionString() {
			return albumSongs.toString();
		}
		
		/**
		 *@return albumString String that represents the album
		 */
		public String toString() {
			return this.albumString;
		}

}