#include "MapResHandle.h"
#include "tinyxml2.h"
#include<stdexcept>

//  XMLDocument
//  �h�L�������g�S�̂�\���h�L�������g�I�u�W�F�N�g
//  LoadFile: �t�@�C������XML��ǂݍ��ށB�߂�l�͐��� or �G���[�R�[�h
//  XMLElement* root = doc.FirstChildElement : root�̍ŏ�ʗv�f���擾����B���O�w��\


void TileTextureRegistry::LoadFilesPath(const std::string& xml_path) {
    //  ���[�g�̎擾�p
    std::string tmp_root_top = "Tiles";
    std::string tmp_root_second = "Tile";
    std::string tmp_root_file = "file";


    //  XML�S�̂���������ɓǂݍ���Ńc���[�\���Ƃ��ĕێ�����N���X
    //  root�擾�A�v�f����ȂǑS�Ă����ōs����
    _TINYXML XMLDocument doc;

    
    //  XML�t�@�C���̓Ǎ�
    //  ����������O���Ԃ��Ă���B1�ȏ�͑S�ăG���[�Ȃ�
    const _TINYXML XMLError err = doc.LoadFile(xml_path.c_str());

    //  �t�@�C���̓W�J��������āA���s�Ȃ��O��f��
    if (err != _TINYXML XML_SUCCESS)throw std::runtime_error("TileTextureRegistry::LoadFilesPath : �t�@�C���̓Ǎ��Ɏ��s���܂���");

    //  root�̍ŏ�ʂ��擾����iXML�̃^�O�j
    //  �����Ȃ�XMLElement* �̃|�C���^���Ԃ��Ă���
    const _TINYXML XMLElement* root = doc.FirstChildElement(tmp_root_top.c_str());

    //  ���[�g�̎擾����
    //  ���s�Ȃ��O���͂�
    if (!root) throw std::runtime_error("TileTextureRegistry::LoadFilesPath : ���[�g�̎擾�Ɏ��s���܂���");


    //  ���[�g�̗v�f�̑������擾����
    const char* tmp_basePath = root->Attribute("textureBasePath");
    //  ���������݂�����Z�b�g���āA�Ȃ���΋󕶎�
    tiles_base_path_ = tmp_basePath ? tmp_basePath : "";

    //  �����̃}�b�v���N���A����
    tiles_file_path_.clear();

    //  ���[�g�̗v�f�����Ԃɓǂݍ���
    for (const _TINYXML XMLElement* tileElement = root->FirstChildElement(tmp_root_second.c_str()); //  ���[�g���g������
        tileElement != nullptr; //  tileElement�ɒ��g�����݂��Ă���Ԃ̓��[�v
        tileElement = tileElement->NextSiblingElement(tmp_root_second.c_str())) {   //  ���[�g�̉��̊K�w�̃��m���擾����

        //  id�����𐮐��Ƃ��Ď擾�A�Ȃ��ꍇ�́[�P(�s���l)��Ԃ�
        int tmp_id = tileElement->IntAttribute("id", -1);

        //  id�̓Ǎ�����
        if (tmp_id < 0) throw std::runtime_error("TileTextureRegistry::LoadFilesPath : ������ID��ǂݍ���ł��܂�");

        //  file�����𕶎���Ŏ擾�i�e�N�X�`���t�@�C�����j
        const char* fileAttr = tileElement->Attribute(tmp_root_file.c_str());

        if (!fileAttr) throw std::runtime_error("TileTextureRegistry::LoadFilesPath :�@�����ȃe�N�X�`���t�@�C������ǂݍ���ł��܂�");

        //  �x�[�X�p�X�ƃt�@�C���p�X��ǂݍ���ID��key�ɂ��R���N�V�����ɓ����
        tiles_file_path_[tmp_id] = tiles_base_path_ + fileAttr;
        int a;

    }
}

std::string TileTextureRegistry::GetPath(int tile_id) const {
    auto it = tiles_file_path_.find(tile_id);
    if (it != tiles_file_path_.end()) return it->second;
    throw std::runtime_error("TileTextureRegistry::GetPath : ������ID���n����Ă��܂�");
}
