#include "HitBOxRenderComp.h"
#include "Camera.h"
#include "GameObject.h"
#include "ColliderComp.h"
#include "GetColor.h"

void HitBoxRenderComp::Render()
{

#ifdef _DEBUG



	//	�K�v�ȃR���|�[�Ntp�����邩�ǂ����̔���
	if (!GetGameObj()->GetComponent<ColliderComp>())return;


	//	�擾
	auto camera_pos = Camera::Instance().position();
	auto camera_size = Camera::Instance().area_size();

	//	���W
	const auto& trans = GetGameObj()->transform.WorldPosition();


	//	�T�C�Y
	const auto& size = GetGameObj()->GetComponent<ColliderComp>()->size();
	Vector2D<float> draw = trans - camera_pos + (camera_size / 2);

	DrawBoxAA(draw.x, draw.y, draw.x + size.x, draw.y + size.y,
		RED, FALSE);
#endif // _DEBUG

}
