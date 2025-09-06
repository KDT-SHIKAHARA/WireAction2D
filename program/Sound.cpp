#include "Sound.h"
#include "DxLib.h"


void Sound::Play(int PlayType){
	if (IsPlay())
		return;
	PlaySoundMem(resource_->GetHandle(), PlayType);
}

void Sound::Stop(){
	if (!IsPlay())
		return;
	StopSoundMem(resource_->GetHandle());
}

bool Sound::IsPlay() const{
	return CheckSoundMem(resource_->GetHandle());
}

//	‰¹—Ê‚Ì•ÏX
void Sound::SetVolume(float arg_volumeRatio){
	int final_volume = (float)volume_ * arg_volumeRatio;
	ChangeVolumeSoundMem(final_volume,resource_->GetHandle());
}
