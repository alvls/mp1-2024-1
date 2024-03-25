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

	void addsong(Song song)
	{
		songs.push_back(song);
		std::sort(songs.begin(), songs.end(), [](const Song& a, const Song& b) {return a.title < b.title; });
	}

	void modifysong(const std::string& title, const std::string& artist)
	{
		Song* it;
		try
		{
			it = findsong(title, artist);
		}
		catch (const std::string& e)
		{
			std::cerr << "Error: " << e << std::endl;
		}
		_modmenu(*it);
	}
	
	Song* findsong(const std::string& title, const std::string& artist)
	{
		auto it = std::find_if(songs.begin(), songs.end(), [&](const Song& song) {return song.title == title && song.artist == artist; });
		if (it == songs.end())
		{
			throw(std::string )
		}
	}

private:
	void _modmenu(Song song)
	{
		return;
	}
};