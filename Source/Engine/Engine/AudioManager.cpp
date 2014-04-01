//////////////////////////////////////////////////////////////////////////////
// Filename: AudioManager.cpp
///////////////////////////////////////////////////////////////////////////////
#include "AudioManager.h"
#include "DebugDefinitions.h"

AudioManager::AudioManager()
{
	directSound = 0;
	primaryBuffer = 0;
	jumpSoundPath    = new string;
	rollSoundPath    = new string;
	injuredSoundPath = new string;
	deathSoundPath   = new string;
	jumpSounds    = new ArrayList<IDirectSoundBuffer8>;
	rollSounds    = new ArrayList<IDirectSoundBuffer8>;
	injuredSounds = new ArrayList<IDirectSoundBuffer8>;
	deathSounds   = new ArrayList<IDirectSoundBuffer8>;
	
}
 
 
AudioManager::AudioManager(const AudioManager& other)
{
}
 
 
AudioManager::~AudioManager()
{
	if (jumpSoundPath)
	{
		delete jumpSoundPath;
		jumpSoundPath = 0;
	}
	if (rollSoundPath)
	{
		delete rollSoundPath;
		rollSoundPath = 0;
	}
	if (injuredSoundPath)
	{
		delete injuredSoundPath;
		injuredSoundPath = 0;
	}
	if (deathSoundPath)
	{
		delete deathSoundPath;
		deathSoundPath = 0;
	}

	if (jumpSounds)
	{
		delete jumpSounds;
		jumpSounds = 0;
	}
	if (rollSounds)
	{
		delete rollSounds;
		rollSoundPath = 0;
	}
	if (injuredSounds)
	{
		delete injuredSounds;
		injuredSounds = 0;
	}
	if (deathSounds)
	{
		delete deathSounds;
		deathSounds = 0;
	}
}
 
 
bool AudioManager::initialize(HWND hwnd)
{
	bool result;

	// Initialize direct sound and the primary sound buffer.
	result = InitializeDirectSound(hwnd);
	if(!result)
	{
		return false;
	}

    result = InitializeDirectSound(hwnd);
	if(!result)
	{
		return false;
	}

	//Set paths to sounds
	*jumpSoundPath    = "audio/tempjump.wav";
	*rollSoundPath    = "audio/roll.wav";
	*injuredSoundPath = "audio/hit.wav";
	*deathSoundPath   = "audio/wawawa.wav";
     
	// Load a wave audio file onto a secondary buffer.
	result = LoadWaveFile("audio/Avalanche.wav", &song01);
	if(!result)
	{
		return false;
	}
 
	return true;
}

void AudioManager::Shutdown()
{
	// Release the secondary buffers.
	ShutdownWaveFile(&song01);

	// Release path names
	if (jumpSoundPath)
	{
		delete jumpSoundPath;
		jumpSoundPath = 0;
	}
	// Release arrays of playing sounds
	if (jumpSounds)
	{
		delete jumpSounds;
		jumpSounds = 0;
	}

	// Shutdown the Direct Sound API.
	ShutdownDirectSound();
 
	return;
}

bool AudioManager::InitializeDirectSound(HWND hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
 
 
	// Initialize the direct sound interface pointer for the default sound device.
	result = DirectSoundCreate8(NULL, &directSound, NULL);
	if(FAILED(result))
	{
		return false;
	}
 
	// Set the cooperative level to priority so the format of the primary sound buffer can be modified.
	result = directSound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
	if(FAILED(result))
	{
		return false;
	}
	// Setup the primary buffer description.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
 
	// Get control of the primary sound buffer on the default sound device.
	result = directSound->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Setup the format of the primary sound bufffer.
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the primary buffer to be the wave format specified.
	result = primaryBuffer->SetFormat(&waveFormat);
	if(FAILED(result))
	{
		return false;
	}
 
	return true;
}

void AudioManager::ShutdownDirectSound()
{
	// Release the primary sound buffer pointer.
	if(primaryBuffer)
	{
		primaryBuffer->Release();
		primaryBuffer = 0;
	}
 
	// Release the direct sound interface pointer.
	if(directSound)
	{
		directSound->Release();
		directSound = 0;
	}
 
	return;
}

bool AudioManager::LoadWaveFile(const char* filename, IDirectSoundBuffer8** secondaryBuffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;
	// Open the wave file in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if(error != 0)
	{
		return false;
	}
 
	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if(count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') || 
	   (waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}
 
	// Check that the file format is the WAVE format.
	if((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
	   (waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}
 
	// Check that the sub chunk ID is the fmt format.
	if((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
	   (waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}
 
	// Check that the audio format is WAVE_FORMAT_PCM.
	if(waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}
  
	// Ensure that the wave file was recorded in 16 bit format.
	if(waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}
	
 
	// Check for the data chunk header.
	if((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
	   (waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}
	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;
 
	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;
		// Create a temporary sound buffer with the specific buffer settings.
	result = directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if(FAILED(result))
	{
		return false;
	}
 
	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if(FAILED(result))
	{
		return false;
	}
 
	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;
	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);
 
	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader.dataSize];
	if(!waveData)
	{
		return false;
	}
 
	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if(count != waveFileHeader.dataSize)
	{
		return false;
	}
 
	// Close the file once done reading.
	error = fclose(filePtr);
	if(error != 0)
	{
		return false;
	}
 
	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if(FAILED(result))
	{
		return false;
	}
 
	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);
 
	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if(FAILED(result))
	{
		return false;
	}
	
	// Release the wave data since it was copied into the secondary buffer.
	delete [] waveData;
	waveData = 0;
 
	return true;
}

void AudioManager::ShutdownWaveFile(IDirectSoundBuffer8** secondaryBuffer)
{
	// Release the secondary sound buffer.
	if(*secondaryBuffer)
	{
		(*secondaryBuffer)->Release();
		*secondaryBuffer = 0;
	}

	return;
}

void AudioManager::update()
{
	IDirectSoundBuffer8* temp;
	DWORD status;
	for (int i = 0; i < jumpSounds->size(); i++)
	{
		jumpSounds->elementAt(i)->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			temp = jumpSounds->elementAt(i);
			jumpSounds->remove(temp);
			//delete temp;
		}
	}
	for (int i = 0; i < rollSounds->size(); i++)
	{
		rollSounds->elementAt(i)->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			temp = rollSounds->elementAt(i);
			rollSounds->remove(temp);
			//delete temp;
		}
	}
	for (int i = 0; i < injuredSounds->size(); i++)
	{
		injuredSounds->elementAt(i)->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			temp = injuredSounds->elementAt(i);
			injuredSounds->remove(temp);
			//delete temp;
		}
	}
	for (int i = 0; i < deathSounds->size(); i++)
	{
		deathSounds->elementAt(i)->GetStatus(&status);
		if (!(status & DSBSTATUS_PLAYING))
		{
			temp = deathSounds->elementAt(i);
			deathSounds->remove(temp);
			//delete temp;
		}
	}
}

bool AudioManager::PlaySong01()
{
	HRESULT result;

	result = song01->SetCurrentPosition(0);
	if(FAILED(result))
	{
		return false;
	}

	result = song01->SetVolume(DSBVOLUME_MAX - 1500);
	if(FAILED(result))
	{
		return false;
	}

	result = song01->Play(0, 0, 1);

	if(FAILED(result))
	{
		return false;
	}
 
	return true;
}

bool AudioManager::StopSong01()
{
	HRESULT result;

	result = song01->Stop();

	if(FAILED(result))
	{
		return false;
	}
 
	return true;
}

bool AudioManager::PlayWave(IDirectSoundBuffer8* sound, int gain = 0)
{
	HRESULT result;
 
	// Set position at the beginning of the sound buffer.
	result = sound->SetCurrentPosition(0);
	if(FAILED(result))
	{
		return false;
	}
 
	// Set volume of the buffer
	result = sound->SetVolume(DSBVOLUME_MAX + gain);
	if(FAILED(result))
	{
		return false;
	}
 
	// Play the contents of the secondary sound buffer.
	result = sound->Play(0, 0, 0);
	
	if(FAILED(result))
	{
		return false;
	}
 
	return true;
}

void AudioManager::onStateStart(PlayerState& state)
{
	
	if (state.getStateType() == PlayerStateType::PST_JUMP)
	{
		if (AUDIO_DEBUG) writeTextToConsole(L"Jump!");

		playJumpSound();

		/*
		IDirectSoundBuffer8* jumpSound;
		LoadWaveFile(jumpSoundPath->c_str(), &jumpSound);
		jumpSounds->add(jumpSound);
		PlayWave(jumpSounds->elementAt(jumpSounds->size()-1),-1500);
		*/
	}
	else if (state.getStateType() == PlayerStateType::PST_ROLL)
	{
		if (AUDIO_DEBUG) writeTextToConsole(L"Roll!");

		playRollSound();

		/*
		IDirectSoundBuffer8* rollSound;
		LoadWaveFile(rollSoundPath->c_str(), &rollSound);
		rollSounds->add(rollSound);
		PlayWave(rollSounds->elementAt(rollSounds->size()-1),-1500);
		*/
	}
	else if (state.getStateType() == PlayerStateType::PST_INJURED)
	{
		if (AUDIO_DEBUG) writeTextToConsole(L"Injured!");

		playInjuredSound();

		/*
		IDirectSoundBuffer8* injuredSound;
		LoadWaveFile(injuredSoundPath->c_str(), &injuredSound);
		injuredSounds->add(injuredSound);
		PlayWave(injuredSounds->elementAt(injuredSounds->size()-1),-1100);
		*/
	}
}

void AudioManager::onStateEnd(PlayerState& state)
{
	if (state.getStateType() == PlayerStateType::PST_JUMP)
	{

	}
	else if (state.getStateType() == PlayerStateType::PST_ROLL)
	{

	}
	else if (state.getStateType() == PlayerStateType::PST_INJURED)
	{

	}
}

// Functions below initially made for menus
// Cut and pasted from the state functions you made

void AudioManager::playRollSound()
{		
	IDirectSoundBuffer8* rollSound;
	LoadWaveFile(rollSoundPath->c_str(), &rollSound);
	rollSounds->add(rollSound);
	PlayWave(rollSounds->elementAt(rollSounds->size()-1),-1500);

}

void AudioManager::playInjuredSound()
{
	IDirectSoundBuffer8* injuredSound;
	LoadWaveFile(injuredSoundPath->c_str(), &injuredSound);
	injuredSounds->add(injuredSound);
	PlayWave(injuredSounds->elementAt(injuredSounds->size()-1),-1100);
}

void AudioManager::playJumpSound()
{
	IDirectSoundBuffer8* jumpSound;
	LoadWaveFile(jumpSoundPath->c_str(), &jumpSound);
	jumpSounds->add(jumpSound);
	PlayWave(jumpSounds->elementAt(jumpSounds->size()-1),-1500);
}

void AudioManager::playDeathSound()
{
	IDirectSoundBuffer8* deathSound;
	LoadWaveFile(deathSoundPath->c_str(), &deathSound);
	deathSounds->add(deathSound);
	PlayWave(deathSounds->elementAt(deathSounds->size()-1),-1700);
}