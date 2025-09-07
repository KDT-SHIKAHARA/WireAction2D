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


	//	�}�E�X���W
    Vector2Di mouse;
    const auto& camera_pos = Camera::Instance().position();
    const auto& camera_size = Camera::Instance().area_size();

    mouse.x = camera_pos.x + (sx - camera_size .x / 2);
    mouse.y = camera_pos.y + (sy - camera_size.y  / 2);

	//	���l�𕶎���ɕϊ�����CSV�����ŕۑ�����
	std::ofstream ofs(filePath, std::ios::app);
	if (!ofs)return;

	ofs << mouse.x << "," << mouse.y << "\n";

}

PointSaver::PointSaver()
{
	path_table_[KEY_INPUT_1] = "res/needle/pos2.txt";
    path_table_[KEY_INPUT_2] = "res/goal/pos2.txt";
    path_table_[KEY_INPUT_3] = "res/player/pos/2.txt";
}

void PointSaver::Update()
{
	for (const auto& path : path_table_) {
		//	���͔���
		if (Input::IsKeyOn(path.first)) {
			Log(path.second);
		}
	}
	//	�t�@�C���p�X��n���āA���̃t�@�C���p�X�̃t�H���_�ɍ��W��ǉ�����

}

std::vector<Vector2Df> PointSaver::GetPoints(const std::string& filePath)
{

    std::vector<Vector2Df> points;
    std::ifstream ifs(filePath);
    if (!ifs) {
        // �J���Ȃ������ꍇ�͋��vector��Ԃ�
        return points;
    }

    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string sx, sy;
        if (std::getline(iss, sx, ',') && std::getline(iss, sy)) {
            Vector2Df pt = { std::stof(sx), std::stof(sy) };
            points.push_back(pt);
        }
    }
    return points;
}

