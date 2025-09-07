#pragma once
#pragma once
#include<set>
#include<string>


/// <summary>
/// �^�O��Player:Enemy�̂悤�ɏ������đ��݂���g�ݍ��킹�Ȃ瓖���蔻����s��
/// </summary>
class CollisionRule {
	std::set<std::string> m_collisionPairs;	 //	�y�A���m�̃^�O�͓����蔻����s��

	//	�g�ݍ��킹�擾
	std::string makeKey(const std::string& a_tag1, const std::string& a_tag2)const {
		return (a_tag1 < a_tag2) ? a_tag1 + ":" + a_tag2 : a_tag2 + ":" + a_tag1;
	}

public:
	//	�g�ݍ��킹�̒ǉ�
	void AddRule(const std::string& a_tag1, const std::string& a_tag2) {
		m_collisionPairs.insert(makeKey(a_tag1, a_tag2));
	}

	//	�����蔻����s�����ǂ����̔���
	//	true; �s�� 
	//	false: �s��Ȃ�
	bool CanCollide(const std::string& a_tag1, const std::string& a_tag2)const {
		return m_collisionPairs.contains(makeKey(a_tag1, a_tag2));
	}

	//	�S�Ă̑g�ݍ��킹�擾
	const std::set<std::string>& GetAllRules()const {
		return m_collisionPairs;
	}

};