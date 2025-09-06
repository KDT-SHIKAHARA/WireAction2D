#pragma once
#include<random>
#include<cassert>


//	std::random_deviceは生成時にバードウェアの乱数が行われる
//	_STD is_integral<T>::valueはTが整数型かを判定する。
//	STD mt19937は生成機能にハードウェアの乱数を投げて完全ランダムなテーブルを作成する。



class RandomManager {
	//	std::random_device を使ってランダムの作成
	RandomManager():gen(rand()){}

	virtual ~RandomManager() = default;
public:
	RandomManager(const RandomManager&) = delete;
	RandomManager& operator=(const RandomManager&) = delete;

	static RandomManager& Instance() {
		static RandomManager instance;
		return instance;
	}

	//	範囲内の整数乱数を生成するメソッド
	int GetInt(const int& arg_min, const int& arg_max) {
		assert(arg_min < arg_max);
		_STD uniform_int_distribution<> dist(arg_min, arg_max);
		return dist(gen);
	}

	//	範囲内の浮動小数点までの乱数を生成するメソッド
	double GetDouble(const double& arg_min, const double& arg_max) {
		assert(arg_min < arg_max);
		_STD uniform_real_distribution<> dist(arg_min, arg_max);
	}

	//	任意の範囲内の乱数を生成する汎用
	template<typename T>
	T GetRandom(const double& arg_min, const double& arg_max) {
		assert(arg_min < arg_max);	//	最小値は最大値より小さくないといけない
		if (_STD is_integral<T>::value) {
			//	整数型のランダムを返す。
			_STD uniform_int_distribution<> dist(arg_min, arg_max);
			return dist(gen);
		}
		
		//	浮動小数点型のランダムを返す
		_STD uniform_real_distribution<> dist(arg_min, arg_max);
		return dist(gen);
	}


private:
	_STD mt19937 gen;	//	乱数エンジン
	_STD random_device rand;	//	ハードウェア乱数作成用

};


/// <summary>
/// RandomManagerラッパー
/// </summary>
class Random {
public:
	/// <summary>
	/// 範囲内の整数乱数を生成する
	/// </summary>
	/// <param name="arg_min">	最小値	</param>
	/// <param name="arg_max">	最大値	</param>
	/// <returns>	範囲内のランダムな整数値	</returns>
	int GetInt(const int& arg_min, const int& arg_max) {
		return RandomManager::Instance().GetInt(arg_min, arg_max);
	}

	/// <summary>
	/// 範囲内の浮動小数点までの乱数を生成する
	/// </summary>
	/// <param name="arg_min">	最小値	</param>
	/// <param name="arg_max">	最大値	</param>
	/// <returns>	範囲内のランダムな浮動小数点型	</returns>
	double GetDouble(const double& arg_min, const double& arg_max) {
		return RandomManager::Instance().GetDouble(arg_min, arg_max);
	}

	/// <summary>
	/// 任意の範囲内の乱数を生成する汎用
	/// </summary>
	/// <typeparam name="T">	整数型 or 浮動小数点型	</typeparam>
	/// <param name="arg_min">	最小値	</param>
	/// <param name="arg_max">	最大値	</param>
	/// <returns>	任意の型のランダムな値	</returns>
	template<typename T>
	T GetRandom(const double& arg_min, const double& arg_max) {
		return RandomManager::Instance().GetRandom(arg_min, arg_max);
	}
};