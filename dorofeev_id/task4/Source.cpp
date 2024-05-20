#include "SongList.h"


int main()
{
	SongList list1;
	try 
	{
		list1.readFromFile("test_in.txt");
		std::cout << list1.getSongsQuantity() << std::endl;
		std::vector<Song> lol = list1.getAllByArtist("singer");
		list1.addSong({ "lax", "sngr", "cmpsr", "poettt", "", {01, 12, 2101 } });
		list1.addSong({ "zzz", "sngr", "cmpsr", "poettt", "", {01, 12, 2101 } });
		std::vector<Song>::iterator fnd = list1.findSong("lol", "singer");
		list1.deleteSong("lol1", "singer2");
		list1.modifySong("lol", "singer", "Release", "05.12.1977");
		list1.saveToFile("test_out.txt");
	}
	catch (const std::string& e)
	{
		std::cerr << "Error: " << e << std::endl;
	}
	system("pause");
	return 0;
}