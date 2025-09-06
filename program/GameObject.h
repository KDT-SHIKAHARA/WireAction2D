#pragma once
#include<memory>		//	スマートポインタと自身のshared_ptr確保
#include<unordered_map>	//	順列がどうでもよくて、検索を高速にするため
#include<typeindex>		//	型をキーにするため
#include<type_traits>	//	型情報調べるため
#include"transform.h"	//	座標系
#include"Component.h"
#include "DrawableComp.h"
#include"flag.h"
#include"tag.h"
#include<map>

//	改良するならメモを参考にしてください
//	メモ 
//	作成		: 2025.7.16
//	最終更新	: 2025.7.16
//	std::unordered_map	:順列がどうでもよい、検索を高速、型をキーにするから。
//	std::type_index		:type_info をハッシュ・比較可能なオブジェクトに変換。　イメージは型をキーとして扱う
//	typeid (T)			:T の型情報を取得（戻り値は const type_info&）　イメージは型を引数にしてる感じ


/// <summary>
/// コンポーネントをアタッチするための画面上のオブジェクトの元
/// コンポーネントは、unityでいうスクリプトのイメージ。
/// </summary>
class GameObject :public std::enable_shared_from_this<GameObject> {
	using Component_map = std::unordered_map<std::type_index, std::shared_ptr<Component>>;	//	型が長いので。
	Component_map components_;	//	コンポーネント一覧
	std::vector<std::shared_ptr<DrawableComp>> drawableComps_;	//	描画系コンポーネント
	std::string tag_;	//	識別用タグ
public:
	Transform transform;	//	座標系直接座標などにアクセスできないのでpublicで
	Flag isDestroyed = false;	//	消滅判定

	GameObject() = default;
	virtual ~GameObject() = default;

	//	componentの追加（同じものがあると重複するので上書きする）
	//	右辺値ならムーブ、左辺値ならコピーをしたいので転送参照で右辺値かどうかのわかる状態で引数でもらう。
	//	戻り値は基本的に受け取る必要がないが、作るときにそのコンポーネントのメソッドを管理側で呼びやすくなる。
	//	別途読み込むなら別に戻り値なくてもいいけど..ねっ？
	template<typename T,typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args);

	//	componentの取得
	//	指定した型のcomponentを戻り値として返す。
	template<typename T>
	std::shared_ptr<T> GetComponent()const;

	//	全てのcomponentの更新を呼ぶ
	virtual void Update();

	//	全てのcomponentの描画を呼ぶ
	virtual void Render();


	//	tag
	void SetTag(const std::string& tag) { tag_ = tag; }
	const std::string& GetTag()const { return tag_; }

	//	layer
	void SortLayer();

};

template<typename T, typename ...Args>
inline std::shared_ptr<T> GameObject::AddComponent(Args&&... args){
	static_assert(std::is_base_of<Component, T>::value, "その型は、class componentを継承していません");
	//	componentの生成
	//	std::forwardで右辺値ならmove、左辺値ならコピーをする
	auto comp = std::make_shared<T>(std::forward<Args>(args)...);
	//	付与したcomponentのGameObjectを自分にする。
	comp->SetGameObj(shared_from_this());
	//	T型と同じキーの型の中身に入れる。(すでにあればリセットされる)
	components_[std::type_index(typeid (T))] = comp;

	//	描画系のコンポーネントなら
	if (auto drawable = std::dynamic_pointer_cast<DrawableComp>(comp)) {
		drawableComps_.push_back(drawable);
	}


	//	作ったcomponentを一応返す
	return comp;
}


template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent() const{
	//	検索して、イテレータを格納 成功ならその場所のイテレータ、失敗なら.endを返す
	auto ite = components_.find(std::type_index(typeid(T)));
	//	検索に成功しているかを判定
	if (ite != components_.end()) {
		//	基底クラス型から派生型にポインタを変換する。
		return std::static_pointer_cast<T>(ite->second);
	}
	//	なければnullptrを返して、if分などでfalseになるようにする
	return nullptr;
}
