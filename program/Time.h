#pragma once
#include<chrono>

//	std::chrono::steady_clock::time_point 
//	システム依存じゃない時間をミリ秒で保存する。
//	精度がそこまで重要じゃなくて、現在時刻が必要ない場合これ
//	time_pointで時間の数値を保存する変数になる。

//	elapsedは経過時間

class TimeManager {
	//	初期化
	TimeManager(float artg_frame_rate = 60,float arg_time_scale = 1.0)
		:before_time_(_CHRONO steady_clock::now()), delta_time_(0.0), time_(0.0), 
		time_since_start_(0.0),time_scale_(arg_time_scale){}
	
	virtual ~TimeManager() = default;
public:
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;

	static TimeManager& Instance() {
		static TimeManager instance;
		return instance;
	}

	/// <summary>
	///	現在時間を取得して、前フレームからの経過時間を計測して、各フィールドに足したあと今回の時間を足す。
	/// </summary>
	void Update() {
		auto tmp_current_time = _CHRONO steady_clock::now();	//	現在時間の取得
		_CHRONO duration<double> tmp_elapsed = tmp_current_time - before_time_;	//	経過時間の計算
		delta_time_ = tmp_elapsed.count() * time_scale_;	//	経過時間を時間比率分の速度で加速させる
		time_ += delta_time_;	//	総時間の経過
		time_since_start_ += delta_time_;	//	設定した時からの時間計測
		before_time_ = tmp_current_time;	//	フレームの更新
	}


	//	時間経過の比率の設定
	void SetTimeScale(const float& arg_timeScale) { time_scale_ = arg_timeScale; }

	//	計測開始時間の設定
	void SetStartPoint() { time_since_start_ = 0.0; }


	//	取得
	double deltaTime()const { return  delta_time_; }
	double time()const { return time_; }
	double timeSinceStart()const { return time_since_start_; }
	float timeScale()const { return time_scale_; }

private:
	_CHRONO steady_clock::time_point before_time_;	//	前フレームの時間(ミリ単位)
	double delta_time_;	//	フレーム間の経過時間
	double time_;	//	総経過時間
	double time_since_start_;	//	設定したタイミングから経過した時間の計測
	float time_scale_;	//	ゲーム内と現実時間の経過比率(加速用)

};

/// <summary>
/// 時間管理クラスのラッパー
/// </summary>
class Time {
public:
	/// <summary>
	///	現実時間を基準として、ゲーム内でのゲーム時間の加速度を設定する。
	/// 1.0で現実時間と同じ
	/// 2.0で二倍速になる。
	/// </summary>
	/// <param name="arg_timeScale">	設定するゲーム内時間の比率	</param>
	static void SetTimeScale(const float& arg_timeScale) {
		TimeManager::Instance().SetTimeScale(arg_timeScale);
	}

	/// <summary>
	/// 任意で設定した地点からの経過時間を計測する。
	/// ストップウォッチ機能
	/// </summary>
	static void SetStartPoint() {
		TimeManager::Instance().SetStartPoint();
	}

	/// <summary>
	/// 現実の時間を基準として、１フレームの間の経過時間を返す。
	/// </summary>
	/// <returns> フレーム間の経過時間 </returns
	static double deltaTime(){
		return TimeManager::Instance().deltaTime();
	}

	/// <summary>
	/// 現実時間基準の起動してからの経過時間を返す
	/// </summary>
	/// <returns>	総経過時間	</returns>
	static double time() {
		TimeManager::Instance().time();
	}

	/// <summary>
	/// 設定した開始地点からの経過時間を返す。
	/// </summary>
	/// <returns> 設定地点からの経過時間 </returns>
	static double timeSinceStart() {
		TimeManager::Instance().timeSinceStart();
	}

	/// <summary>
	/// ゲーム内の時間と現実時間の比率
	/// 現実の経過速度に倍率をかけることでゲーム内ではその倍速で経過する
	/// </summary>
	/// <returns> 経過倍率 </returns>
	static float timeScale() {
		TimeManager::Instance().timeScale();
	}

};