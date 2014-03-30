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

//#include "PlayerSounds.h"
#include "Player.h"
#include "ArrayList.h"
#include "DebugDefinitions.h"

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

	bool initialize(HWND);
	bool PlaySong01();
	bool StopSong01();
	void Shutdown();

	void onStateStart(PlayerState&);
	void onStateEnd(PlayerState&);

	// Sound playback functions (initially made for menus)

	void playRollSound();
	void playInjuredSound();
	void playJumpSound();

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	bool LoadWaveFile(const char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);

	bool PlayWave(IDirectSoundBuffer8*, int);
 
private:
	IDirectSound8* directSound;
	IDirectSoundBuffer* primaryBuffer;
	IDirectSoundBuffer8* song01;
	string* jumpSoundPath;
	ArrayList<IDirectSoundBuffer8>* jumpSounds;
	string* rollSoundPath;
	ArrayList<IDirectSoundBuffer8>* rollSounds;
	string* injuredSoundPath;
	ArrayList<IDirectSoundBuffer8>* injuredSounds;
	
};