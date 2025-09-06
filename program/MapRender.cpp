#include"MapRender.h"
#include"TextureResourceMng.h"
#include"dxlib.h"
#include"GetColor.h"
#include<cassert>
/// <summary>
/// �t�@�C���p�X�Ǘ�����t�@�C���p�X���擾���āA�e�N�X�`����ǂݍ���ł���
/// </summary>
/// <param name="tiles_file_path"></param>
void MapRender::LoadTexture(const std::unordered_map<int, std::string>& tiles_file_path){
	for (auto& [num, filepath] : tiles_file_path) {
		tile_textures_[num] = TextureResourceMgr::Instance().GetTexture(filepath);
		assert(tile_textures_[num]->GetHandle() != -1);
	}
}

/// <summary>
///	�J�����̍��W���g���ăf�B�X�v���C�ɉf��ꏊ�ɂ���^�C�������`�悷��
/// </summary>
/// <param name="mapData"> �}�b�v�f�[�^�̃R���N�V�������i�[�����N���X </param>
/// <param name="camera">  </param>
void MapRender::Render(const MapData& mapData) {
	Vector2D<float> camera_pos = Camera::Instance().position();
	Vector2D<float> camera_size = Camera::Instance().area_size();
	int map_size = mapData.GetTileSize();

	//	�}�b�v�̕`��͈͂̍���ƉE���̔ԍ��擾
	
	//int left   =	(camera_pos.x - camera_size.x / 2) / map_size;
	//int right =		(camera_pos.x + camera_size.x / 2) / map_size;
	//int top =		(camera_pos.y - camera_size.y / 2) / map_size;
	//int bottom =	(camera_pos.y + camera_size.y / 2) / map_size;

	int left = static_cast<int>(std::floor((camera_pos.x - camera_size.x / 2) / map_size));
	int right = static_cast<int>(std::ceil((camera_pos.x + camera_size.x / 2) / map_size));
	int top = static_cast<int>(std::floor((camera_pos.y - camera_size.y / 2) / map_size));
	int bottom = static_cast<int>(std::ceil((camera_pos.y + camera_size.y / 2) / map_size));

	//	�K�v�ӏ��̂ݕ`��
	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {

			if (x < 0 || y < 0 || x >= mapData.GetMapW() || y >= mapData.GetMapH()) {
				continue;
			}
			//	�}�b�v�^�C���̎擾
			const Tile& tile = mapData.GetTile(x, y);

			//	0�ԂȂ珈�����s��Ȃ�
			//	�����0�Ԃ̎������ł���悤�ɃC���X�^���X�͎������Ă�������
			//	�������Ȃ��ق�����������
			
			if (!isDraw(tile.id)) continue;

			//	�`����W�̎擾
			//int drawX = x * map_size - (camera_pos.x + camera_size.x / 2);
			//int drawY = y * map_size - (camera_pos.y + camera_size.y / 2);

			int drawX = static_cast<int>(x * map_size - camera_pos.x + camera_size.x / 2);
			int drawY = static_cast<int>(y * map_size - camera_pos.y + camera_size.y / 2);
			//	�`��


			DrawBox(drawX, drawY, drawX + map_size, drawY + map_size, BLUE, TRUE);
			DrawGraph(drawX, drawY, tile_textures_[tile.id]->GetHandle(), TRUE);
		}
	}



}