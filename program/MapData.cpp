#include "MapData.h"
#include<stdexcept>
#include"MapLoader.h"

//	初期化
MapData::MapData():tile_size_(32), map_max_w_(0), map_max_h_(0){
}

/// <summary>
/// ファイル読込クラスの読込メソッドを作って、マップデータを入れたTiles型のオブジェクトを返す
/// </summary>
/// <param name="filePath"> マップデータが入っているファイル </param>
void MapData::LoadMapData(const std::string& filePath){
	//	読込メソッド
	tiles_ = MapLoader::Load(filePath);

	////	サイズ取得
	map_max_w_ = tiles_[0].size();
	map_max_h_ = tiles_.size();

}

/// <summary>
/// 指定したインデックスのタイルのconst参照を返す。
/// インデックスが範囲外なら例外を吐く
/// </summary>
/// <param name="arg_x"> 第二要素数のインデックス </param>
/// <param name="arg_y"> 第一要素数のインデックス </param>
/// <returns></returns>
const Tile& MapData::GetTile(int index_x, int index_y) const {
	if (index_x < 0 || index_y < 0 || index_x >= map_max_w_ || index_y >= map_max_h_)
	{
		return Tile{};
	}
	return  tiles_[index_y][index_x];
}
