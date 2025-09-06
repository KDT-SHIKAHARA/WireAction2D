#include"MapLoader.h"
#include<fstream>
#include<sstream>
#include<unordered_set>
#include<stdexcept>
#include<cassert>

/// <summary>
/// 文字列を「，」の前で区切ってTileクラスに格納する。
/// </summary>
/// <param name="str"> ファイルから読み込んだ1行単位 </param>
/// <param name="delimiter"> 区切る文字 </param>
/// <returns> 1行単位のTileクラス達 </returns>
std::vector<Tile> MapLoader::split(const std::string& str, char delimiter) {
	std::vector<Tile> tmp_row;	
	std::istringstream tmp_csvLine(str);
	std::string tmp_strBuf;	

	while (std::getline(tmp_csvLine,tmp_strBuf,delimiter)){
		int tmp_map_num = std::stoi(tmp_strBuf);
		//	バグってた箇所はここ
		assert(tmp_map_num < TileType::Max);
		if (tmp_map_num >= TileType::Max) throw std::out_of_range("MapLoader::split: 読み込んだマップ番号が最大値を越しています");
		tmp_row.push_back(
			{ tmp_map_num,TileShape::Rect, CheckCollisionFlag(tmp_map_num) });
	}

	return tmp_row;
}

/// <summary>
/// 当たり判定をするかどうかを判定するメソッド
/// </summary>
/// <param name="map_num"></param>
/// <returns></returns>
bool MapLoader::CheckCollisionFlag(int map_num){
	//	コンテナに当たり判定をする要素を格納
	static const std::unordered_set<int> conllidable_nums = { 1,2};

	//	コンテナ内にあればtrue　なければflase
	return conllidable_nums.count(map_num) > 0;
}

/// <summary>
/// ファイルからマップデータを読み込んでTileクラス達に格納する
/// </summary>
/// <param name="filepath"> ファイルのフルパス </param>
/// <returns> マップデータを格納したTileクラスのコレクションを返す </returns>
std::vector<std::vector<Tile>> MapLoader::Load(const std::string& filepath) {
	std::ifstream file(filepath);
	std::vector<std::vector<Tile>> tmp_map_data;
	std::string tmp_line_str;

	//	全て取得	
	while (std::getline(file, tmp_line_str)) {
		tmp_map_data.push_back(split(tmp_line_str));
	}
	
	//	マップデータを格納したTileのコレクションを返す
	return tmp_map_data;
}
