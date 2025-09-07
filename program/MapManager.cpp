#include"MapManager.h"
#include"Rect.h"
#include"GameObject.h"
#include"ColliderComp.h"
#include"RigidbodyComp.h"
#include <cmath>
#include<algorithm>
#include"Time.h"

/// <summary>
/// �}�b�v�Ƃ̓����蔻����s���B
/// ���\�b�h�̌Ăяo���O�ɓ����蔻����s����I�u�W�F�N�g�����肵�Ă���Ăяo��
/// </summary>
/// <param name="gameObj"></param>
void MapManager::CheckCollision(const std::vector<std::shared_ptr<GameObject>>& gameObjs){

	for (auto gameObj : gameObjs) {
		CheckAABB(gameObj);
	}

}

/// <summary>
/// �}�b�v�ƃ��C���[�̃A���J�[���������Ă��邩�ǂ����𔻒肷��
/// </summary>
/// <param name="anchor_pos"> �A���J�[���W </param>
/// <returns> true: �A���J�[�ݒu false: ���ݒu </returns>
bool MapManager::CheckPointHit(const Vector2D<float>& anchor_pos)
{
	const auto& tile_size = mapData_.GetTileSize();

	int anchor_x = static_cast<int>(anchor_pos.x) / tile_size;
	int anchor_y = static_cast<int>(anchor_pos.y) / tile_size;

	if (!mapData_.GetTile(anchor_x, anchor_y).isCollision) return false;

	return true;
}

bool MapManager::CheckAABB(std::shared_ptr<GameObject> gameObj)
{
	//	rigidbody�Acollider�̃|�C���^�擾
	auto rigid_ptr = gameObj->GetComponent<RigidbodyComp>();
	auto collider_ptr = gameObj->GetComponent<ColliderComp>();

	//	�擾�ł��Ȃ���ΏI��
	if (!rigid_ptr || !collider_ptr)return false;

	//	���W�擾
	const auto& pos = gameObj->transform.WorldPosition();
	//	�T�C�Y�擾
	const auto& size = collider_ptr->size();
	//	�ړ��ʎ擾
	const auto& velocity = rigid_ptr->velocity();


	//	�}�b�v�^�C���̃T�C�Y
	const auto& tile_size = mapData_.GetTileSize();

	//	�����������ǂ����̔���
	bool isHit = false;

	//	�v���C���[�̓����蔻��pRect�쐬
	Rect current_GameObj{ pos.x,pos.y,size.x,size.y };

	//	�ړ�����͂��̍��W
	Rect next_GameObj = current_GameObj;
	next_GameObj.x += velocity.x;
	next_GameObj.y += velocity.y;


	//	�Փ˃`���b�N������͈�
	int left = (int)std::floor(next_GameObj.x / tile_size);
	int right = (int)std::floor((next_GameObj.x + next_GameObj.w) / tile_size);
	int top = (int)std::floor(next_GameObj.y / tile_size);
	int bottom = (int)std::floor((next_GameObj.y + next_GameObj.h) / tile_size);

	//	�␳���錻�݂̈ړ��x�N�g��
	Vector2D<float> new_velocity = velocity;

	//	������
	next_GameObj = current_GameObj;
	next_GameObj.x += velocity.x;

	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			if (!mapData_.IsInMap(x, y)) continue;
			if (!mapData_.GetTile(x, y).isCollision) continue;

			//	�����蔻�������^�C���̋�`
			Rect tile{
				(float)(x * tile_size),
				(float)(y * tile_size),
				(float)(tile_size),
				(float)(tile_size),
			};

			//	�����蔻��
			if (next_GameObj.IsCollision(tile)) {
				//	�����߂��ʂ̌v�Z
				if (velocity.x > 0) {	//	�E����
					new_velocity.x = tile.x - (current_GameObj.x + current_GameObj.w);
				}
				else if (velocity.x < 0) { //	������
					new_velocity.x = (tile.x + tile.w) - current_GameObj.x;
				}

				isHit = true;

			}
		}
	}


	//	���̕␳��̍��W�ŏc�����̌v�Z
	current_GameObj.x += new_velocity.x;

	//	�Ō�ɐڒn�����ς��邽�߂�bool
	Flag isGround = false;


	//	�c�ړ�
	next_GameObj = current_GameObj;
	next_GameObj.y += velocity.y;

	//	���̕␳��̃}�b�v�ԍ�
	left = (int)std::floor(next_GameObj.x / tile_size);
	right = (int)std::floor((next_GameObj.x + next_GameObj.w) / tile_size);
	top = (int)std::floor(next_GameObj.y / tile_size);
	bottom = (int)std::floor((next_GameObj.y + next_GameObj.h) / tile_size);

	//	�ŏI�I��Y���̈ړ���
	float current_vec_y = velocity.y;


	for (int y = top; y <= bottom; y++) {
		for (int x = left; x <= right; x++) {
			if (!mapData_.IsInMap(x, y)) continue;
			if (!mapData_.GetTile(x, y).isCollision) continue;

			//	�����蔻�������^�C���̋�`
			Rect tile{
				(float)(x * tile_size),
				(float)(y * tile_size),
				(float)(tile_size),
				(float)(tile_size),
			};

			//	�����蔻��
			if (next_GameObj.IsCollision(tile)) {
				if (velocity.y > 0) {	//	������
					//	�����蔻�������^�C���̏㑤���W
					float limit = tile.y - (current_GameObj.y + current_GameObj.h);
					//	�㑤���W��艺��������߂荞��ł���
					if (limit < current_vec_y) {
						current_vec_y = limit;
						isGround = true;

					}
				}
				else if (velocity.y <= 0) {	//	�����
					float limit = (tile.y + tile.h) - current_GameObj.y;
					if (limit > current_vec_y) {
						current_vec_y = limit;
					}

				}

				isHit = true;


			}
			new_velocity.y = current_vec_y;

		}
	}

	//	�␳�������x���Z�b�g
	rigid_ptr->SetVelocity(new_velocity / Time::deltaTime());



	//	�ݒu����𔽉f
	if (isGround) {
		rigid_ptr->isGravity_.Set(false);
		rigid_ptr->isGrounded_.Set(true);
	}
	else {
		rigid_ptr->isGravity_.Set(true);
		rigid_ptr->isGrounded_.Set(false);
	}

	return isHit;

}

/// <summary>
/// �t�@�C������t�@�C���p�X��ǂݍ����
/// �t�@�C������摜��ǂݍ���
/// </summary>
void MapManager::Load(const std::string& map_data) {
	render_.LoadTexture(registry_.tiles_file_path());
	mapData_.LoadMapData(map_data);


}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera"> �J�����N���X�̍��W���擾 </param>
void MapManager::Render() {
	try
	{
		//	�`��
		render_.Render(mapData_);

	}
	catch (const std::exception&)
	{
		
	}
}