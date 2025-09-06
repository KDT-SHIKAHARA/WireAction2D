#pragma once

/// <summary>
/// 描画を行うメソッドこのクラスを継承する。
/// 更新、描画を持つクラスで、両方オーバーライドしないといけないで、確約したい場合と
/// ポインタキャストで描画このクラスを継承している場合だけ処理をする。
/// </summary>
class DrawableComp{
protected:
	int layer_ = 0;
public:
	int GetLayer()const { return layer_; }
	virtual ~DrawableComp() = default;
	virtual void Render() = 0;
};