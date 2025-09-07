#pragma once
#pragma once
#include<set>
#include<string>


/// <summary>
/// タグをPlayer:Enemyのように所持して存在する組み合わせなら当たり判定を行う
/// </summary>
class CollisionRule {
	std::set<std::string> m_collisionPairs;	 //	ペア同士のタグは当たり判定を行う

	//	組み合わせ取得
	std::string makeKey(const std::string& a_tag1, const std::string& a_tag2)const {
		return (a_tag1 < a_tag2) ? a_tag1 + ":" + a_tag2 : a_tag2 + ":" + a_tag1;
	}

public:
	//	組み合わせの追加
	void AddRule(const std::string& a_tag1, const std::string& a_tag2) {
		m_collisionPairs.insert(makeKey(a_tag1, a_tag2));
	}

	//	当たり判定を行うかどうかの判定
	//	true; 行う 
	//	false: 行わない
	bool CanCollide(const std::string& a_tag1, const std::string& a_tag2)const {
		return m_collisionPairs.contains(makeKey(a_tag1, a_tag2));
	}

	//	全ての組み合わせ取得
	const std::set<std::string>& GetAllRules()const {
		return m_collisionPairs;
	}

};