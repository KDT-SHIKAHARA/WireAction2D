#include"MapRender.h"
#include"TextureResourceMng.h"
#include"dxlib.h"
#include"GetColor.h"
#include<cassert>
/// <summary>
/// ファイルパス管理からファイルパスを取得して、テクスチャを読み込んでいる
/// </summary>
/// <param name="tiles_file_path"></param>
void MapRender::LoadTexture(const std::unordered_map<int, std::string>& tiles_file_path){
	for (auto& [num, filepath] : tiles_file_path) {
		tile_textures_[num] = TextureResourceMgr::Instance().GetTexture(filepath);
		assert(tile_textures_[num]->GetHandle() != -1);
	}
}

/// <summary>
///	カメラの座標を使ってディスプレイに映る場所にいるタイルだけ描画する
/// </summary>
/// <param name="mapData"> マップデータのコレクションを格納したクラス </param>
/// <param name="camera">  </param>
void MapRender::Render(const MapData& mapData) {
	Vector2D<float> camera_pos = Camera::Instance().position();
	Vector2D<float> camera_size = Camera::Instance().area_size();
	int map_size = mapData.GetTileSize();

	//	マップの描画範囲の左上と右下の番号取得
	
	//int left   =	(camera_pos.x - camera_size.x / 2) / map_size;
	//int right =		(camera_pos.x + camera_size.x / 2) / map_size;
	//int top =		(camera_pos.y - camera_size.y / 2) / map_size;
	//int bottom =	(camera_pos.y + camera_size.y / 2) / map_size;

	int left = static_cast<int>(std::floor((camera_pos.x - camera_size.x / 2) / map_size));
	int right = static_cast<int>(std::ceil((camera_pos.x + camera_size.x / 2) / map_size));
	int top = static_cast<int>(std::floor((camera_pos.y - camera_size.y / 2) / map_size));
	int bottom = static_cast<int>(std::ceil((camera_pos.y + camera_size.y / 2) / map_size));

	//	必要箇所のみ描画
	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {

			if (x < 0 || y < 0 || x >= mapData.GetMapW() || y >= mapData.GetMapH()) {
				continue;
			}
			//	マップタイルの取得
			const Tile& tile = mapData.GetTile(x, y);

			//	0番なら処理を行わない
			//	今後の0番の実装をできるようにインスタンスは実装しておくけど
			//	実装しないほうがいいかも
			
			if (!isDraw(tile.id)) continue;

			//	描画座標の取得
			//int drawX = x * map_size - (camera_pos.x + camera_size.x / 2);
			//int drawY = y * map_size - (camera_pos.y + camera_size.y / 2);

			int drawX = static_cast<int>(x * map_size - camera_pos.x + camera_size.x / 2);
			int drawY = static_cast<int>(y * map_size - camera_pos.y + camera_size.y / 2);
			//	描画


			DrawBox(drawX, drawY, drawX + map_size, drawY + map_size, BLUE, TRUE);
			DrawGraph(drawX, drawY, tile_textures_[tile.id]->GetHandle(), TRUE);
		}
	}



}