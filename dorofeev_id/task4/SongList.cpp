#include "SongList.h"

void SongList::addSong(Song song)
{
	songs.push_back(song);
	std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {return a.title < b.title; });
}

void SongList::modifySong(const std::string& title, const std::string& artist, const std::string& key, const std::string newInf)
{
	try
	{
		auto it = findSong(title, artist);
		_mod(*it, key, newInf);
	}
	catch (const std::string& e)
	{
		std::cerr << "Error: " << e << std::endl;
	}
}

std::vector<Song>::iterator SongList::findSong(const std::string& title, const std::string& artist)
{
	auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song) {return song.title == title && song.artist == artist; });
	if (it == songs.end())
	{
		throw std::string("Song can`t be found");
	}
	else
	{
		return it;
	}
}

std::vector<Song> SongList::getAllByPoet(const std::string& poet)
{
	std::vector<Song> gotbypoet;
	for (auto x : songs)
	{
		if (x.poet == poet)
			gotbypoet.push_back(x);
	}
	std::sort(gotbypoet.begin(), gotbypoet.end(), [](const Song& a, const Song& b) {return a.title < b.title; });

	return gotbypoet;
}

std::vector<Song> SongList::getAllByComposer(const std::string& composer)
{
	std::vector<Song> gotbycomposer;
	for (auto x : songs)
	{
		if (x.composer == composer)
			gotbycomposer.push_back(x);
	}
	std::sort(gotbycomposer.begin(), gotbycomposer.end(), [](const Song& a, const Song& b) {return a.title < b.title; });

	return gotbycomposer;
}

std::vector<Song> SongList::getAllByArtist(const std::string& artist)
{
	std::vector<Song> gotbyartist;
	for (auto x : songs)
	{
		if (x.artist == artist)
			gotbyartist.push_back(x);
	}
	std::sort(gotbyartist.begin(), gotbyartist.end(), [](const Song& a, const Song& b) {return a.title < b.title; });

	return gotbyartist;
}

int SongList::getSongsQuantity()
{
	return songs.size();
}

void SongList::deleteSong(const std::string& title, const std::string& artist)
{
	songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const Song& song) { return song.title == title && song.artist == artist; }), songs.end());
}

void SongList::saveToFile(const std::string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		throw std::string("File is not opened");
	}

	for (const auto& song : songs)
	{
		file << "Title: " << song.title << std::endl
			<< "Artist: " << song.artist << std::endl
			<< "Composer: " << song.composer << std::endl
			<< "Poet: " << song.poet << std::endl
			<< "Release date: " << song.releaseDate.day << "." << song.releaseDate.month << "." << song.releaseDate.year << std::endl;

		if (!song.album.empty())
			file << "Album: " << song.album << std::endl;

		file << "-------------------------------------------------------" << std::endl;
	}

	file.close();
}

void SongList::readFromFile(const std::string& filename)
{
	songs.clear();
	std::ifstream file(filename);
	std::string line;
	Song currentSong;
	if (!file.is_open())
	{
		throw std::string("File is not opened");
	}

	while (std::getline(file, line))
	{
		if (line == "-------------------------------------------------------")
		{
			addSong(currentSong);
			currentSong = Song();
		}
		else
		{
			std::istringstream iss(line);
			std::string key, value;
			iss >> key >> std::ws;
			std::getline(iss, value);

			if (key == "Title:")
				currentSong.title = value;
			else if (key == "Artist:")
				currentSong.artist = value;
			else if (key == "Composer:")
				currentSong.composer = value;
			else if (key == "Poet:")
				currentSong.poet = value;
			else if (key == "Release")
			{
				std::string dateStr = value.substr(value.find(":") + 2);
				std::istringstream dateIss(dateStr);
				char dot;
				dateIss >> currentSong.releaseDate.day >> dot >> currentSong.releaseDate.month >> dot >> currentSong.releaseDate.year;
			}
			else if (key == "Album:")
				currentSong.album = value;
		}
	}

	if (!currentSong.title.empty())
		addSong(currentSong);

	file.close();
}

void SongList::_mod(Song& song, const std::string& key, const std::string& newInf)
{
	if (key == "Title:")
		song.title = newInf;
	else if (key == "Artist:")
		song.artist = newInf;
	else if (key == "Composer:")
		song.composer = newInf;
	else if (key == "Poet:")
		song.poet = newInf;
	else if (key == "Release")
	{
		std::istringstream dateIss(newInf);
		char dot;
		dateIss >> song.releaseDate.day >> dot >> song.releaseDate.month >> dot >> song.releaseDate.year;
	}
	else if (key == "Album:")
		song.album = newInf;
	else
		throw std::string("Invalid key");
}