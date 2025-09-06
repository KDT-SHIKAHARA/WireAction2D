#pragma once
#include<random>
#include<cassert>


//	std::random_device�͐������Ƀo�[�h�E�F�A�̗������s����
//	_STD is_integral<T>::value��T�������^���𔻒肷��B
//	STD mt19937�͐����@�\�Ƀn�[�h�E�F�A�̗����𓊂��Ċ��S�����_���ȃe�[�u�����쐬����B



class RandomManager {
	//	std::random_device ���g���ă����_���̍쐬
	RandomManager():gen(rand()){}

	virtual ~RandomManager() = default;
public:
	RandomManager(const RandomManager&) = delete;
	RandomManager& operator=(const RandomManager&) = delete;

	static RandomManager& Instance() {
		static RandomManager instance;
		return instance;
	}

	//	�͈͓��̐��������𐶐����郁�\�b�h
	int GetInt(const int& arg_min, const int& arg_max) {
		assert(arg_min < arg_max);
		_STD uniform_int_distribution<> dist(arg_min, arg_max);
		return dist(gen);
	}

	//	�͈͓��̕��������_�܂ł̗����𐶐����郁�\�b�h
	double GetDouble(const double& arg_min, const double& arg_max) {
		assert(arg_min < arg_max);
		_STD uniform_real_distribution<> dist(arg_min, arg_max);
	}

	//	�C�ӂ͈͓̔��̗����𐶐�����ėp
	template<typename T>
	T GetRandom(const double& arg_min, const double& arg_max) {
		assert(arg_min < arg_max);	//	�ŏ��l�͍ő�l��菬�����Ȃ��Ƃ����Ȃ�
		if (_STD is_integral<T>::value) {
			//	�����^�̃����_����Ԃ��B
			_STD uniform_int_distribution<> dist(arg_min, arg_max);
			return dist(gen);
		}
		
		//	���������_�^�̃����_����Ԃ�
		_STD uniform_real_distribution<> dist(arg_min, arg_max);
		return dist(gen);
	}


private:
	_STD mt19937 gen;	//	�����G���W��
	_STD random_device rand;	//	�n�[�h�E�F�A�����쐬�p

};


/// <summary>
/// RandomManager���b�p�[
/// </summary>
class Random {
public:
	/// <summary>
	/// �͈͓��̐��������𐶐�����
	/// </summary>
	/// <param name="arg_min">	�ŏ��l	</param>
	/// <param name="arg_max">	�ő�l	</param>
	/// <returns>	�͈͓��̃����_���Ȑ����l	</returns>
	int GetInt(const int& arg_min, const int& arg_max) {
		return RandomManager::Instance().GetInt(arg_min, arg_max);
	}

	/// <summary>
	/// �͈͓��̕��������_�܂ł̗����𐶐�����
	/// </summary>
	/// <param name="arg_min">	�ŏ��l	</param>
	/// <param name="arg_max">	�ő�l	</param>
	/// <returns>	�͈͓��̃����_���ȕ��������_�^	</returns>
	double GetDouble(const double& arg_min, const double& arg_max) {
		return RandomManager::Instance().GetDouble(arg_min, arg_max);
	}

	/// <summary>
	/// �C�ӂ͈͓̔��̗����𐶐�����ėp
	/// </summary>
	/// <typeparam name="T">	�����^ or ���������_�^	</typeparam>
	/// <param name="arg_min">	�ŏ��l	</param>
	/// <param name="arg_max">	�ő�l	</param>
	/// <returns>	�C�ӂ̌^�̃����_���Ȓl	</returns>
	template<typename T>
	T GetRandom(const double& arg_min, const double& arg_max) {
		return RandomManager::Instance().GetRandom(arg_min, arg_max);
	}
};