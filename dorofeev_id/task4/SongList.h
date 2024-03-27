#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdexcept>

struct Date
{
	int day;
	int month;
	int year;
};

struct Song
{
	std::string title;
	std::string poet;
	std::string composer;
	std::string artist; //исполнитель
	std::string album;
	Date releaseDate;
};

class SongList
{
private:
	std::vector<Song> songs;

public:
	void addSong(Song song);
	void modifySong(const std::string& title, const std::string& artist, const std::string& key, const std::string newInf);
	std::vector<Song>::iterator findSong(const std::string& title, const std::string& artist);
	std::vector<Song> getAllByPoet(const std::string& poet);
	std::vector<Song> getAllByComposer(const std::string& composer);
	std::vector<Song> getAllByArtist(const std::string& artist);
	int getSongsQuantity();
	void deleteSong(const std::string& title, const std::string& artist);
	void saveToFile(const std::string& filename);
	void readFromFile(const std::string& filename);
	 //осталось:_modMenu

private:
	void _mod(Song& song, const std::string& key, const std::string& newInf);
};