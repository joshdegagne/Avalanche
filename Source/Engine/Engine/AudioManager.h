///////////////////////////////////////////////////////////////////////////////
// Filename: AudioManager.h
///////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

#include "PlayerSounds.h"
#include "Player.h"
#include "ArrayList.h"

///////////////////////////////////////////////////////////////////////////////
// Class name: AudioManager
///////////////////////////////////////////////////////////////////////////////
class AudioManager : public IPlayerListener
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:
	AudioManager();
	AudioManager(const AudioManager&);
	~AudioManager();

	bool Initialize(HWND);
	bool PlayWave(IDirectSoundBuffer8*);
	void Shutdown();
	void update();

	void onStateStart(PlayerState&);
	void onStateEnd(PlayerState&);

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
 
 
private:
	IDirectSound8* directSound;
	IDirectSoundBuffer* primaryBuffer;
	IDirectSoundBuffer8* song01;
	IDirectSoundBuffer8* jumpSound;
	ArrayList<Player*> players;
	ArrayList<IDirectSoundBuffer8*> playingSounds;
	
};