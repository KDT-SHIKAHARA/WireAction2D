#pragma once
#include<memory>		//	�X�}�[�g�|�C���^�Ǝ��g��shared_ptr�m��
#include<unordered_map>	//	���񂪂ǂ��ł��悭�āA�����������ɂ��邽��
#include<typeindex>		//	�^���L�[�ɂ��邽��
#include<type_traits>	//	�^��񒲂ׂ邽��
#include"transform.h"	//	���W�n
#include"Component.h"
#include "DrawableComp.h"
#include"flag.h"
#include"tag.h"
#include<map>

//	���ǂ���Ȃ烁�����Q�l�ɂ��Ă�������
//	���� 
//	�쐬		: 2025.7.16
//	�ŏI�X�V	: 2025.7.16
//	std::unordered_map	:���񂪂ǂ��ł��悢�A�����������A�^���L�[�ɂ��邩��B
//	std::type_index		:type_info ���n�b�V���E��r�\�ȃI�u�W�F�N�g�ɕϊ��B�@�C���[�W�͌^���L�[�Ƃ��Ĉ���
//	typeid (T)			:T �̌^�����擾�i�߂�l�� const type_info&�j�@�C���[�W�͌^�������ɂ��Ă銴��


/// <summary>
/// �R���|�[�l���g���A�^�b�`���邽�߂̉�ʏ�̃I�u�W�F�N�g�̌�
/// �R���|�[�l���g�́Aunity�ł����X�N���v�g�̃C���[�W�B
/// </summary>
class GameObject :public std::enable_shared_from_this<GameObject> {
	using Component_map = std::unordered_map<std::type_index, std::shared_ptr<Component>>;	//	�^�������̂ŁB
	Component_map components_;	//	�R���|�[�l���g�ꗗ
	std::vector<std::shared_ptr<DrawableComp>> drawableComps_;	//	�`��n�R���|�[�l���g
	std::string tag_;	//	���ʗp�^�O
public:
	Transform transform;	//	���W�n���ڍ��W�ȂǂɃA�N�Z�X�ł��Ȃ��̂�public��
	Flag isDestroyed = false;	//	���Ŕ���

	GameObject() = default;
	virtual ~GameObject() = default;

	//	component�̒ǉ��i�������̂�����Əd������̂ŏ㏑������j
	//	�E�Ӓl�Ȃ烀�[�u�A���Ӓl�Ȃ�R�s�[���������̂œ]���Q�ƂŉE�Ӓl���ǂ����̂킩���Ԃň����ł��炤�B
	//	�߂�l�͊�{�I�Ɏ󂯎��K�v���Ȃ����A���Ƃ��ɂ��̃R���|�[�l���g�̃��\�b�h���Ǘ����ŌĂт₷���Ȃ�B
	//	�ʓr�ǂݍ��ނȂ�ʂɖ߂�l�Ȃ��Ă���������..�˂��H
	template<typename T,typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	//	component�̎擾
	//	�w�肵���^��component��߂�l�Ƃ��ĕԂ��B
	template<typename T>
	std::shared_ptr<T> GetComponent()const;

	//	�S�Ă�component�̍X�V���Ă�
	virtual void Update();

	//	�S�Ă�component�̕`����Ă�
	virtual void Render();


	//	tag
	void SetTag(const std::string& tag) { tag_ = tag; }
	const std::string& GetTag()const { return tag_; }

	//	layer
	void SortLayer();

};

template<typename T, typename ...Args>
inline std::shared_ptr<T> GameObject::AddComponent(Args&&... args){
	static_assert(std::is_base_of<Component, T>::value, "���̌^�́Aclass component���p�����Ă��܂���");
	//	component�̐���
	//	std::forward�ŉE�Ӓl�Ȃ�move�A���Ӓl�Ȃ�R�s�[������
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);
	//	�t�^����component��GameObject�������ɂ���B
	comp->SetGameObj(shared_from_this());
	//	T�^�Ɠ����L�[�̌^�̒��g�ɓ����B(���łɂ���΃��Z�b�g�����)
	components_[std::type_index(typeid (T))] = comp;

	//	�`��n�̃R���|�[�l���g�Ȃ�
	if (auto drawable = std::dynamic_pointer_cast<DrawableComp>(comp)) {
		drawableComps_.push_back(drawable);
	}


	//	�����component���ꉞ�Ԃ�
	return comp;
}


template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent() const{
	//	�������āA�C�e���[�^���i�[ �����Ȃ炻�̏ꏊ�̃C�e���[�^�A���s�Ȃ�.end��Ԃ�
	auto ite = components_.find(std::type_index(typeid(T)));
	//	�����ɐ������Ă��邩�𔻒�
	if (ite != components_.end()) {
		//	���N���X�^����h���^�Ƀ|�C���^��ϊ�����B
		return std::static_pointer_cast<T>(ite->second);
	}
	//	�Ȃ����nullptr��Ԃ��āAif���Ȃǂ�false�ɂȂ�悤�ɂ���
	return nullptr;
}
