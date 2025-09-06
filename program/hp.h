#pragma once
#include<algorithm>
#include<cassert>





namespace status {
	/// <summary>
	/// �I�[�o�[�q�[�����s�\�ȑ̗̓N���X
	/// </summary>
	class HP final {
		int current_;	//	���݂�hp
		int max_;	//	�ő�hp
		bool alive_;	//	��������
		bool invincible_ = false;	//	���G����

		//	��������ݒ�
		void clamp() { current_ = std::clamp(current_, 0, max_); }

	public:
		//	������
		HP(int arg_max = 100) :max_(arg_max), current_(arg_max) {
			assert(arg_max > 0);
			alive_ = true;
		}

		virtual ~HP() = default;

		//	��
		void Heal(int arg_amount) {
			if (!is_alive()) return;	//	��������
			current_ += arg_amount;	//	��
			clamp();	//	�͈͐ݒ�
		}

		//	�_���[�W
		void Damage(int arg_amount) {
			if (is_invivcible()) return;	//	���G�Ȃ�_���[�W�������I��
			current_ -= arg_amount;	//	��
			clamp();	//	�͈͐ݒ�
		}

		//	HP��0.0�`1.0�ŕ\��
		float Percent() {
			return (current_ / max_);
		}

		//	���G�t���O
		void Set_invivcible(bool arg_flag) { invincible_ = arg_flag; }

		//	�ő�HP�̍X�V
		void Set_Max(int arg_max) { max_ = arg_max; }

		//	�擾
		int GetCurrent()const { return current_; }
		int GetMax()const { return max_; }
		bool is_alive()const { return alive_; }
		bool is_invivcible()const { return invincible_; }



		//	��������
		explicit operator bool() const { return is_alive(); }


	};

}

