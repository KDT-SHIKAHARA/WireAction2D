#include "MapResHandle.h"
#include "tinyxml2.h"
#include<stdexcept>

//  XMLDocument
//  ドキュメント全体を表すドキュメントオブジェクト
//  LoadFile: ファイルからXMLを読み込む。戻り値は成功 or エラーコード
//  XMLElement* root = doc.FirstChildElement : rootの最上位要素を取得する。名前指定可能


void TileTextureRegistry::LoadFilesPath(const std::string& xml_path) {
    //  ルートの取得用
    std::string tmp_root_top = "Tiles";
    std::string tmp_root_second = "Tile";
    std::string tmp_root_file = "file";


    //  XML全体をメモリ上に読み込んでツリー構造として保持するクラス
    //  root取得、要素操作など全てこれ一つで行える
    _TINYXML XMLDocument doc;

    
    //  XMLファイルの読込
    //  成功したら０が返ってくる。1以上は全てエラーなど
    const _TINYXML XMLError err = doc.LoadFile(xml_path.c_str());

    //  ファイルの展開判定をして、失敗なら例外を吐く
    if (err != _TINYXML XML_SUCCESS)throw std::runtime_error("TileTextureRegistry::LoadFilesPath : ファイルの読込に失敗しました");

    //  rootの最上位を取得する（XMLのタグ）
    //  成功ならXMLElement* のポインタが返ってくる
    const _TINYXML XMLElement* root = doc.FirstChildElement(tmp_root_top.c_str());

    //  ルートの取得判定
    //  失敗なら例外をはく
    if (!root) throw std::runtime_error("TileTextureRegistry::LoadFilesPath : ルートの取得に失敗しました");


    //  ルートの要素の属性を取得する
    const char* tmp_basePath = root->Attribute("textureBasePath");
    //  属性が存在したらセットして、なければ空文字
    tiles_base_path_ = tmp_basePath ? tmp_basePath : "";

    //  既存のマップをクリアする
    tiles_file_path_.clear();

    //  ルートの要素を順番に読み込む
    for (const _TINYXML XMLElement* tileElement = root->FirstChildElement(tmp_root_second.c_str()); //  ルート中身を検索
        tileElement != nullptr; //  tileElementに中身が存在している間はループ
        tileElement = tileElement->NextSiblingElement(tmp_root_second.c_str())) {   //  ルートの下の階層のモノを取得する

        //  id速性を整数として取得、ない場合はー１(不整値)を返す
        int tmp_id = tileElement->IntAttribute("id", -1);

        //  idの読込判定
        if (tmp_id < 0) throw std::runtime_error("TileTextureRegistry::LoadFilesPath : 無効なIDを読み込んでいます");

        //  file属性を文字列で取得（テクスチャファイル名）
        const char* fileAttr = tileElement->Attribute(tmp_root_file.c_str());

        if (!fileAttr) throw std::runtime_error("TileTextureRegistry::LoadFilesPath :　無効なテクスチャファイル名を読み込んでいます");

        //  ベースパスとファイルパスを読み込んだIDをkeyにもつコレクションに入れる
        tiles_file_path_[tmp_id] = tiles_base_path_ + fileAttr;
        int a;

    }
}

std::string TileTextureRegistry::GetPath(int tile_id) const {
    auto it = tiles_file_path_.find(tile_id);
    if (it != tiles_file_path_.end()) return it->second;
    throw std::runtime_error("TileTextureRegistry::GetPath : 無効なIDが渡されています");
}
