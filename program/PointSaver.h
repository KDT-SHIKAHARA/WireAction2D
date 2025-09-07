#pragma once
#include<string>
#include<map>
#include<vector>
#include"vector2d.h"
#include"singleton.h"

class PointSaver :public Singleton<PointSaver> {

	//	�}�E�X������W���擾���ăt�H���_�ɒǉ�����
	void Log(const std::string& filePath);
public:
	PointSaver();

	//	�X�V
	void Update();

	//	�f�[�^���̂�����
	std::vector<Vector2Df> GetPoints(const std::string& filePath);

private:
	//	���͂̃t�@�C���p�X�̃e�[�u��
	std::map<int, std::string> path_table_;

};
