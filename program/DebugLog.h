#pragma once
#include<string>
#include<sstream>
#include<memory>
#include<vector>
#include"flag.h"
#include"DxLib.h"
#include"input.h"

class DebugDisplayBase {
public:
	virtual ~DebugDisplayBase() = default;
	virtual std::string GetString()const = 0;
};


#ifndef NDEBUG

template<typename T>
class DebugDisp :public DebugDisplayBase {
	std::string label_;
	const T& value_;
public:
	DebugDisp(const std::string& arg_label, const T& arg_value)
		:label_(arg_label),value_(arg_value){ }

	std::string GetString()const override {
		std::ostringstream oss;
		oss << label_ << ": " << value_;

		return oss.str();
	}
};


class DebugDispManager {
	DebugDispManager() 
		:kTextSpacing(20), x_(0), y_(60), listScroolY_(0), debugListMaxY_(0), isDisp(false), isScroll(false){};

	virtual ~DebugDispManager() = default;
public:
	DebugDispManager(const DebugDispManager&) = delete;
	DebugDispManager& operator=(const DebugDispManager&) = delete;

	static DebugDispManager& Instance() {
		static DebugDispManager instance;
		return instance;
	}

	//	�ǉ�
	template<typename T>
	void AddDubug(const std::string& arg_label, const T& arg_value) {
		dubugList.emplace_back(std::make_unique<DebugDisp<T>>(arg_label, arg_value));
	}

	template<typename T>
	void Log(const std::string& arg_label,  T arg_value,int x,int y) {
		if (isDisp) return;

		std::string str;
		{
			std::ostringstream oss;
			oss << arg_label << ": " << arg_value;
			str = oss.str();
		}


		DrawFormatString(x, y, GetColor(255, 0, 0), "%s", str.c_str());
	}

	//	�X�V
	void Update() {
		//	�\���ؑ�
		if (Input::IsKeyOn(KEY_INPUT_F1))
			isDisp.Toggle();
			

		//	�X�N���[���\�؂�ւ�
		if (Input::IsKeyOn(KEY_INPUT_F3))
			isScroll.Toggle();

		//	�\������
		if (!isDisp) return;

		if (isScroll) return;
		//	�}�E�X�z�C�[���̓��͗�
		listScroolY_ += Input::GetMouseWheel() * kTextSpacing;

	}

	//	�\��
	void Render() {
		if (!isDisp)return;
			int draw_y = y_;
			for (const auto& it : dubugList) {
				const auto& str = it->GetString();
				DrawFormatString(x_, draw_y + listScroolY_, GetColor(255, 0, 0), "%s", str.c_str());
				draw_y += kTextSpacing;
			}

			if (!isScroll) return;
			DrawString(0, 40, "�X�N���[���Œ蒆", GetColor(255, 0, 0));

	

	}

private:
	std::vector<std::unique_ptr<DebugDisplayBase>> dubugList;	//	�\�����郊�X�g
	const int kTextSpacing;	//	������̊Ԋu
	const int x_,y_;	//	����W
	int listScroolY_;	//	�}�E�X�z�C�[���̓��͗�
	int debugListMaxY_;
	int log_num_ = 0;
	Flag isDisp;	//	�\�������邩�ǂ����̃t���O
	Flag isScroll;	//	�f�o�b�N�̃X�N���[�����\�ɂ��邩�ǂ���
};

#endif // !NDEBUG


#ifdef NDEBUG
class DebugDispManager {
	DebugDispManager() = default;;
	virtual ~DebugDispManager() = default;
public:
	DebugDispManager(const DebugDispManager&) = delete;
	DebugDispManager& operator=(const DebugDispManager&) = delete;

	static DebugDispManager& Instance() {
		static DebugDispManager instance;
		return instance;
	}

	//	�ǉ�
	template<typename T>
	void AddDubug(const std::string& arg_label, const T& arg_value) {
	}

	template<typename T>
	static void Log(const std::string& arg_label, T arg_value, int x, int y) {
	}


	//	�X�V
	void Update() {
	}

	//	�\��
	void Render() {
	}

};

#endif // NDEBUG

class DebugLog {
public:
	//	�ǉ�
	template<typename T>
	static void AddDubug(const std::string& arg_label, const T& arg_value) {
		DebugDispManager::Instance().AddDubug(arg_label, arg_value);
	}

	template<typename T>
	static void Log(const std::string& arg_label, T arg_value, int x, int y) {
		DebugDispManager::Instance().Log(arg_label, arg_value,x,y);
	}

};