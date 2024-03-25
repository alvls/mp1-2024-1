#pragma once
#include <iostream>
#include <fstream>
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

	void addSong(Song song)
	{
		songs.push_back(song);
		std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {return a.title < b.title; });
	}

	void modifySong(const std::string& title, const std::string& artist)
	{
		std::vector<Song>::iterator it;
		try
		{
			it = findSong(title, artist);
		}
		catch (const std::string& e)
		{
			std::cerr << "Error: " << e << std::endl;
		}
		_modMenu(*it);
	}
	
	std::vector<Song>::iterator findSong(const std::string& title, const std::string& artist)
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

	std::vector<Song> getAllByPoet(const std::string& poet)
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

	std::vector<Song> getAllByComposer(const std::string& composer)
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

	std::vector<Song> getAllByArtist(const std::string& artist)
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

	int getSongsQuantity()
	{
		return songs.size();
	}

	 void deleteSong(const std::string& title, const std::string& artist) 
	 {
        songs.erase(std::remove_if(songs.begin(), songs.end(), [&](const Song& song) { return song.title == title && song.artist == artist; }), songs.end());
     }

	 //

private:
	void _modMenu(Song song)
	{
		return;
	}
};