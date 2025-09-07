#include"MapManager.h"
#include"Rect.h"
#include"GameObject.h"
#include"ColliderComp.h"
#include"RigidbodyComp.h"
#include <cmath>
#include<algorithm>
#include"Time.h"

/// <summary>
/// マップとの当たり判定を行う。
/// メソッドの呼び出し前に当たり判定を行えるオブジェクト化判定してから呼び出す
/// </summary>
/// <param name="gameObj"></param>
void MapManager::CheckCollision(const std::vector<std::shared_ptr<GameObject>>& gameObjs){

	for (auto gameObj : gameObjs) {
		CheckAABB(gameObj);
	}

}

/// <summary>
/// マップとワイヤーのアンカーが当たっているかどうかを判定する
/// </summary>
/// <param name="anchor_pos"> アンカー座標 </param>
/// <returns> true: アンカー設置 false: 未設置 </returns>
bool MapManager::CheckPointHit(const Vector2D<float>& anchor_pos)
{
	const auto& tile_size = mapData_.GetTileSize();

	int anchor_x = static_cast<int>(anchor_pos.x) / tile_size;
	int anchor_y = static_cast<int>(anchor_pos.y) / tile_size;

	if (!mapData_.GetTile(anchor_x, anchor_y).isCollision) return false;

	return true;
}

bool MapManager::CheckAABB(std::shared_ptr<GameObject> gameObj)
{
	//	rigidbody、colliderのポインタ取得
	auto rigid_ptr = gameObj->GetComponent<RigidbodyComp>();
	auto collider_ptr = gameObj->GetComponent<ColliderComp>();

	//	取得できなければ終了
	if (!rigid_ptr || !collider_ptr)return false;

	//	座標取得
	const auto& pos = gameObj->transform.WorldPosition();
	//	サイズ取得
	const auto& size = collider_ptr->size();
	//	移動量取得
	const auto& velocity = rigid_ptr->velocity();


	//	マップタイルのサイズ
	const auto& tile_size = mapData_.GetTileSize();

	//	当たったかどうかの判定
	bool isHit = false;

	//	プレイヤーの当たり判定用Rect作成
	Rect current_GameObj{ pos.x,pos.y,size.x,size.y };

	//	移動するはずの座標
	Rect next_GameObj = current_GameObj;
	next_GameObj.x += velocity.x;
	next_GameObj.y += velocity.y;


	//	衝突チャックをする範囲
	int left = (int)std::floor(next_GameObj.x / tile_size);
	int right = (int)std::floor((next_GameObj.x + next_GameObj.w) / tile_size);
	int top = (int)std::floor(next_GameObj.y / tile_size);
	int bottom = (int)std::floor((next_GameObj.y + next_GameObj.h) / tile_size);

	//	補正する現在の移動ベクトル
	Vector2D<float> new_velocity = velocity;

	//	横方向
	next_GameObj = current_GameObj;
	next_GameObj.x += velocity.x;

	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			if (!mapData_.IsInMap(x, y)) continue;
			if (!mapData_.GetTile(x, y).isCollision) continue;

			//	当たり判定をするタイルの矩形
			Rect tile{
				(float)(x * tile_size),
				(float)(y * tile_size),
				(float)(tile_size),
				(float)(tile_size),
			};

			//	当たり判定
			if (next_GameObj.IsCollision(tile)) {
				//	押し戻す量の計算
				if (velocity.x > 0) {	//	右方向
					new_velocity.x = tile.x - (current_GameObj.x + current_GameObj.w);
				}
				else if (velocity.x < 0) { //	左方向
					new_velocity.x = (tile.x + tile.w) - current_GameObj.x;
				}

				isHit = true;

			}
		}
	}


	//	横の補正後の座標で縦方向の計算
	current_GameObj.x += new_velocity.x;

	//	最後に接地判定を変えるためのbool
	Flag isGround = false;


	//	縦移動
	next_GameObj = current_GameObj;
	next_GameObj.y += velocity.y;

	//	横の補正後のマップ番号
	left = (int)std::floor(next_GameObj.x / tile_size);
	right = (int)std::floor((next_GameObj.x + next_GameObj.w) / tile_size);
	top = (int)std::floor(next_GameObj.y / tile_size);
	bottom = (int)std::floor((next_GameObj.y + next_GameObj.h) / tile_size);

	//	最終的なY軸の移動量
	float current_vec_y = velocity.y;


	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			if (!mapData_.IsInMap(x, y)) continue;
			if (!mapData_.GetTile(x, y).isCollision) continue;

			//	当たり判定をするタイルの矩形
			Rect tile{
				(float)(x * tile_size),
				(float)(y * tile_size),
				(float)(tile_size),
				(float)(tile_size),
			};

			//	当たり判定
			if (next_GameObj.IsCollision(tile)) {
				if (velocity.y > 0) {	//	下方向
					//	当たり判定をするタイルの上側座標
					float limit = tile.y - (current_GameObj.y + current_GameObj.h);
					//	上側座標より下だったらめり込んでいる
					if (limit < current_vec_y) {
						current_vec_y = limit;
						isGround = true;

					}
				}
				else if (velocity.y <= 0) {	//	上方向
					float limit = (tile.y + tile.h) - current_GameObj.y;
					if (limit > current_vec_y) {
						current_vec_y = limit;
					}

				}

				isHit = true;


			}
			new_velocity.y = current_vec_y;

		}
	}

	//	補正した速度をセット
	rigid_ptr->SetVelocity(new_velocity / Time::deltaTime());



	//	設置判定を反映
	if (isGround) {
		rigid_ptr->isGravity_.Set(false);
		rigid_ptr->isGrounded_.Set(true);
	}
	else {
		rigid_ptr->isGravity_.Set(true);
		rigid_ptr->isGrounded_.Set(false);
	}

	return isHit;

}

/// <summary>
/// ファイルからファイルパスを読み込んで
/// ファイルから画像を読み込む
/// </summary>
void MapManager::Load(const std::string& map_data) {
	render_.LoadTexture(registry_.tiles_file_path());
	mapData_.LoadMapData(map_data);


}

/// <summary>
/// 描画
/// </summary>
/// <param name="camera"> カメラクラスの座標を取得 </param>
void MapManager::Render() {
	try
	{
		//	描画
		render_.Render(mapData_);

	}
	catch (const std::exception&)
	{
		
	}
}