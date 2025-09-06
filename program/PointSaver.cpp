#include "PointSaver.h"
#include "input.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include"Camera.h"

void PointSaver::Log(const std::string& filePath)
{

    int sx = Input::MouseX();
    int sy = Input::MouseY();


	//	マウス座標
    Vector2Di mouse;
    const auto& camera_pos = Camera::Instance().position();
    const auto& camera_size = Camera::Instance().area_size();

    mouse.x = camera_pos.x + (sx - camera_size .x / 2);
    mouse.y = camera_pos.y + (sy - camera_size.y  / 2);

	//	数値を文字列に変換してCSV方式で保存する
	std::ofstream ofs(filePath, std::ios::app);
	if (!ofs)return;

	ofs << mouse.x << "," << mouse.y << "\n";

}

PointSaver::PointSaver()
{
	path_table_[KEY_INPUT_1] = "res/enemy/StandBots.txt";
}

void PointSaver::Update()
{
	for (const auto& path : path_table_) {
		//	入力判定
		if (Input::IsKeyOn(path.first)) {
			Log(path.second);
		}
	}
	//	ファイルパスを渡して、そのファイルパスのフォルダに座標を追加する

}

std::vector<Vector2Di> PointSaver::GetPoints(const std::string& filePath)
{

    std::vector<Vector2Di> points;
    std::ifstream ifs(filePath);
    if (!ifs) {
        // 開けなかった場合は空のvectorを返す
        return points;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string sx, sy;
        if (std::getline(iss, sx, ',') && std::getline(iss, sy)) {
            Vector2Di pt = { std::stoi(sx), std::stoi(sy) };
            points.push_back(pt);
        }
    }
    return points;
}

