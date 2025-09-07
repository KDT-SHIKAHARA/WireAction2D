#pragma once
#include<string>
#include<map>
#include<vector>
#include"vector2d.h"
#include"singleton.h"

class PointSaver :public Singleton<PointSaver> {

	//	マウスから座標を取得してフォルダに追加する
	void Log(const std::string& filePath);
public:
	PointSaver();

	//	更新
	void Update();

	//	データ内のやつを作る
	std::vector<Vector2Df> GetPoints(const std::string& filePath);

private:
	//	入力のファイルパスのテーブル
	std::map<int, std::string> path_table_;

};
