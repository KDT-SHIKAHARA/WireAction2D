#pragma once
#include<vector>
#include<memory>
#include"singleton.h"
#include"GameObject.h"



/// <summary>
/// �Q�[���I�u�W�F�N�g�̃C���X�^���X�̊Ǘ�
/// ���ʃ��\�b�h�̌Ăяo��
/// </summary>
class GameObjMgr :public Singleton<GameObjMgr>{
	friend class Singleton<GameObjMgr>;

	GameObjMgr() = default;
	virtual ~GameObjMgr() =default;
	using GameObjList= std::vector<std::shared_ptr<GameObject>>;

	//	�폜�t���O�������Ă���Q�[���I�u�W�F�N�g�̍폜
	void DestroyedGameObjects() {
		gameObjs_.erase(
			std::remove_if(
				gameObjs_.begin(),
				gameObjs_.end(),
				[](const std::shared_ptr<GameObject>& obj) { 
					return obj->isDestroyed;
				}), 
			gameObjs_.end());
	}

public:
	//	�Q�[���I�u�W�F�N�g�̒ǉ�
	void AddGameObject(std::shared_ptr<GameObject> gameObj) {
		gameObjs_.push_back(gameObj);
	};

	//	�X�V
	void Update() {
		for (auto& gameObj : gameObjs_) {
			gameObj->Update();
		}

		//	�폜
		DestroyedGameObjects();

	}

	//	�`��
	void Render() {
		for (auto& gameObj : gameObjs_) {
			gameObj->Render();
		}
	}

	void AllDestroyedGameObjects() {
		gameObjs_.clear();
	}

	const GameObjList& GetGameObjList()const { return gameObjs_; }

	/// <summary>
	/// �^�O�Ō��������āA�Y���̃^�O�̃��X�g��Ԃ�
	/// </summary>
	/// <param name="tag"> tag�̖��O </param>
	/// <returns> �Y���^�O�̃��X�g </returns>
	GameObjList GetGameObjWithTag(const std::string& tag) {
		 //	�V�����Y���p���X�g�̍쐬
		std::vector<std::shared_ptr<GameObject>> tag_gameObj;
		
		//	����
		for (auto& obj : gameObjs_) {
			if (obj->GetTag() == tag) {
				tag_gameObj.push_back(obj);
			}
		}
		return tag_gameObj;
	}

private:
	GameObjList gameObjs_;
};

