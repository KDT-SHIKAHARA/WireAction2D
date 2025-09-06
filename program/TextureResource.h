#pragma once

/// <summary>
/// 画像管管理クラス
/// 生成クラスで生成をして、ゲームマネージャーで管理をする。
/// 1度読み込んだ画像リソースを使いまわす
/// </summary>
class TextureResource {
private:
	//	画像ハンドル
	int handle = -1;

public:
	//	画像ハンドルの設定
	TextureResource(int arg_handle) {
		this->handle = arg_handle;

	}

	//	画像ハンドルの取得
	int GetHandle()const {

		return handle;
	}
};
