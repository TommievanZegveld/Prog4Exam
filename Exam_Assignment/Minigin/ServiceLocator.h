#pragma once
#include <windows.h>
#include <mmsystem.h>

enum class EventSounds
{
	SND_PICKUP
};

class Audio
{
public:
	virtual ~Audio() = default;
	virtual void Play(EventSounds soundID) = 0;
	virtual void Stop(EventSounds soundID) = 0;
	virtual void StopAll() = 0;
};

class ButtonAudio : public Audio
{
public:
	void Play(EventSounds soundID) override
	{
		const wchar_t* fileName = nullptr;

		switch (soundID)
		{
		case EventSounds::SND_PICKUP:
			fileName = L"../Resources/Sounds/Fire.wav";
			break;
		}
		if(fileName != nullptr)
		{
			PlaySoundW(fileName, NULL, SND_FILENAME | SND_ASYNC);
		}
		else { std::cout << "Sound file not correct - ServiceLocator.h" << std::endl; }
	}
	void Stop(EventSounds soundID) override
	{
		switch (soundID)
		{
		case EventSounds::SND_PICKUP:
			
		default:
			PlaySound(NULL, NULL, SND_FILENAME);
		}
	}
	void StopAll() override
	{
		PlaySound(NULL, NULL, SND_FILENAME);
	}
};

class NullAudio final : public Audio
{
public:
	void Play(EventSounds) override{};
	void Stop(EventSounds) override{};
	void StopAll() override{};
};

class ServiceLocator
{
public:
	static void initialize() { audioService = &defaultAudioService; }
	static Audio& GetAudio() { return *audioService; }
	static void RegisterAudioService(Audio* service)
	{
		audioService = (service == nullptr) ? &defaultAudioService : service;
	}

private:
	static Audio* audioService;
	static NullAudio defaultAudioService;
};
