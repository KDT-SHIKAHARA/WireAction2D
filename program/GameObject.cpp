#include "GameObject.h"
#include <algorithm>

/// <summary>
/// componentsの全ての更新を呼ぶ
/// </summary>
void GameObject::Update(){
	//	全ての更新処理を呼び出す
	for (auto& [_, comp] : components_) {
		if (comp) comp->Update();
	}
}


/// <summary>
/// componentsの描画をするクラスのRenderを全て呼ぶ
/// </summary>
void GameObject::Render(){
	////	firstとsecondで分離(firstは今回使わないので[_]で名前を付けてない)
	//for (auto& [_, comp] : components_) {
	//	//	基底クラスに描画があるかをキャストして確認 true: 継承している false: 継承していない 
	//	if (auto drawable = std::dynamic_pointer_cast<DrawableComp>(comp)) {
	//		//	描画
	//		drawable->Render();
	//	}
	//}

	for (auto drawable : drawableComps_) {
		drawable->Render();
	}
}

/// <summary>
/// 描画系コンポーネントのlayerを内部数値順に並び替える
/// どこかでかならず呼んでね 
/// </summary>
void GameObject::SortLayer()
{
	std::sort(drawableComps_.begin(), drawableComps_.end(),
		[](const std::shared_ptr<DrawableComp>& first, const std::shared_ptr<DrawableComp>& second) {
			return first->GetLayer() < second->GetLayer();
		});
}



