#pragma once
#include<chrono>

//	std::chrono::steady_clock::time_point 
//	�V�X�e���ˑ�����Ȃ����Ԃ��~���b�ŕۑ�����B
//	���x�������܂ŏd�v����Ȃ��āA���ݎ������K�v�Ȃ��ꍇ����
//	time_point�Ŏ��Ԃ̐��l��ۑ�����ϐ��ɂȂ�B

//	elapsed�͌o�ߎ���

class TimeManager {
	//	������
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
	///	���ݎ��Ԃ��擾���āA�O�t���[������̌o�ߎ��Ԃ��v�����āA�e�t�B�[���h�ɑ��������ƍ���̎��Ԃ𑫂��B
	/// </summary>
	void Update() {
		auto tmp_current_time = _CHRONO steady_clock::now();	//	���ݎ��Ԃ̎擾
		_CHRONO duration<double> tmp_elapsed = tmp_current_time - before_time_;	//	�o�ߎ��Ԃ̌v�Z
		delta_time_ = tmp_elapsed.count() * time_scale_;	//	�o�ߎ��Ԃ����Ԕ䗦���̑��x�ŉ���������
		time_ += delta_time_;	//	�����Ԃ̌o��
		time_since_start_ += delta_time_;	//	�ݒ肵��������̎��Ԍv��
		before_time_ = tmp_current_time;	//	�t���[���̍X�V
	}


	//	���Ԍo�߂̔䗦�̐ݒ�
	void SetTimeScale(const float& arg_timeScale) { time_scale_ = arg_timeScale; }

	//	�v���J�n���Ԃ̐ݒ�
	void SetStartPoint() { time_since_start_ = 0.0; }


	//	�擾
	double deltaTime()const { return  delta_time_; }
	double time()const { return time_; }
	double timeSinceStart()const { return time_since_start_; }
	float timeScale()const { return time_scale_; }

private:
	_CHRONO steady_clock::time_point before_time_;	//	�O�t���[���̎���(�~���P��)
	double delta_time_;	//	�t���[���Ԃ̌o�ߎ���
	double time_;	//	���o�ߎ���
	double time_since_start_;	//	�ݒ肵���^�C�~���O����o�߂������Ԃ̌v��
	float time_scale_;	//	�Q�[�����ƌ������Ԃ̌o�ߔ䗦(�����p)

};

/// <summary>
/// ���ԊǗ��N���X�̃��b�p�[
/// </summary>
class Time {
public:
	/// <summary>
	///	�������Ԃ���Ƃ��āA�Q�[�����ł̃Q�[�����Ԃ̉����x��ݒ肷��B
	/// 1.0�Ō������ԂƓ���
	/// 2.0�œ�{���ɂȂ�B
	/// </summary>
	/// <param name="arg_timeScale">	�ݒ肷��Q�[�������Ԃ̔䗦	</param>
	static void SetTimeScale(const float& arg_timeScale) {
		TimeManager::Instance().SetTimeScale(arg_timeScale);
	}

	/// <summary>
	/// �C�ӂŐݒ肵���n�_����̌o�ߎ��Ԃ��v������B
	/// �X�g�b�v�E�H�b�`�@�\
	/// </summary>
	static void SetStartPoint() {
		TimeManager::Instance().SetStartPoint();
	}

	/// <summary>
	/// �����̎��Ԃ���Ƃ��āA�P�t���[���̊Ԃ̌o�ߎ��Ԃ�Ԃ��B
	/// </summary>
	/// <returns> �t���[���Ԃ̌o�ߎ��� </returns
	static double deltaTime(){
		return TimeManager::Instance().deltaTime();
	}

	/// <summary>
	/// �������Ԋ�̋N�����Ă���̌o�ߎ��Ԃ�Ԃ�
	/// </summary>
	/// <returns>	���o�ߎ���	</returns>
	static double time() {
		TimeManager::Instance().time();
	}

	/// <summary>
	/// �ݒ肵���J�n�n�_����̌o�ߎ��Ԃ�Ԃ��B
	/// </summary>
	/// <returns> �ݒ�n�_����̌o�ߎ��� </returns>
	static double timeSinceStart() {
		TimeManager::Instance().timeSinceStart();
	}

	/// <summary>
	/// �Q�[�����̎��Ԃƌ������Ԃ̔䗦
	/// �����̌o�ߑ��x�ɔ{���������邱�ƂŃQ�[�����ł͂��̔{���Ōo�߂���
	/// </summary>
	/// <returns> �o�ߔ{�� </returns>
	static float timeScale() {
		TimeManager::Instance().timeScale();
	}

};