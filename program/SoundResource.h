#pragma once

//	create 2025.5.3

class SoundResource {
	int soundHandle;
public:
	SoundResource(int arg_soundHandle):soundHandle(arg_soundHandle){}
	virtual ~SoundResource() = default;

	int GetHandle() { return soundHandle; }

};