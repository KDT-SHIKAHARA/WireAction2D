#pragma once

//	作成日: 2025.7.18
//	更新日:	2025.7.18
//	作成者:	kirito shikahara


/// <summary>
/// 現状は矩形同士かないので必要はないけど円との当たり判定をあとから追加できるように作っておきます
/// もし修正をかけときはこれを使ってください、未来の俺へ
/// </summary>
enum class TileShape {
	None,
	Rect,
	Circle,
};



/// <summary>
/// マップタイルはこのクラスを扱うマップデータクラスでしか直接中身を扱わないのでstructで
/// カプセル化を重視するならclassでアクセサを作ります。
/// </summary>
struct Tile {
	int id = 0;			//	種別識別
	TileShape shape = TileShape::None;	//	形
	bool isCollision = true;	//	当たり判定を行うかどうか
};

