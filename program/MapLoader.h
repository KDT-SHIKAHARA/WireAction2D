#pragma once
#include<string>
#include<vector>
#include"Tile.h"


class MapLoader {
	enum TileType{
		None,
		Grass,
		Platform,
		Max,
	};

	static std::vector<Tile> split(const std::string& str, char delimiter = ',');
	static bool CheckCollisionFlag(int map_num);
public:
	static int TileTypeMax() { return Max; }
	static std::vector<std::vector<Tile>> Load(const std::string& filepath);
};