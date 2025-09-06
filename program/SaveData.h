#pragma once
#include<string>
#include"cereal/function/iobinary.h"

template<typename T>
class SaveData {
public:
	SaveData(const std::string& arg_filePath)
		:filePath_(arg_filePath){ }

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(data_);
	}

	//	セーブデータ
	void Save() {
		SaveBinary(data_, filePath_);
	}

	//	ロード
	void Load() {
		data_ = LoadBinary(filePath_);
	}

private:
	std::string filePath_;
	T data_;
};