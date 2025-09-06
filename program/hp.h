#pragma once
#include<algorithm>
#include<cassert>





namespace status {
	/// <summary>
	/// オーバーヒールが不可能な体力クラス
	/// </summary>
	class HP final {
		int current_;	//	現在のhp
		int max_;	//	最大hp
		bool alive_;	//	生存判定
		bool invincible_ = false;	//	無敵判定

		//	上限下限設定
		void clamp() { current_ = std::clamp(current_, 0, max_); }

	public:
		//	初期化
		HP(int arg_max = 100) :max_(arg_max), current_(arg_max) {
			assert(arg_max > 0);
			alive_ = true;
		}

		virtual ~HP() = default;

		//	回復
		void Heal(int arg_amount) {
			if (!is_alive()) return;	//	生存判定
			current_ += arg_amount;	//	回復
			clamp();	//	範囲設定
		}

		//	ダメージ
		void Damage(int arg_amount) {
			if (is_invivcible()) return;	//	無敵ならダメージ処理を終了
			current_ -= arg_amount;	//	回復
			clamp();	//	範囲設定
		}

		//	HPの0.0～1.0で表示
		float Percent() {
			return (current_ / max_);
		}

		//	無敵フラグ
		void Set_invivcible(bool arg_flag) { invincible_ = arg_flag; }

		//	最大HPの更新
		void Set_Max(int arg_max) { max_ = arg_max; }

		//	取得
		int GetCurrent()const { return current_; }
		int GetMax()const { return max_; }
		bool is_alive()const { return alive_; }
		bool is_invivcible()const { return invincible_; }



		//	生存判定
		explicit operator bool() const { return is_alive(); }


	};

}

