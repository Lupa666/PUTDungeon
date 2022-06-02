#include "SoundPlayer.h"

void SoundPlayer::Init()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	walk[WALK1] = Mix_LoadWAV("sounds/Tup1.wav");
	walk[WALK2] = Mix_LoadWAV("sounds/Tup2.wav");
	walk[WALK3] = Mix_LoadWAV("sounds/Tup3.wav");
	walk[WALK4] = Mix_LoadWAV("sounds/tup4.wav");

	attack[HIT1] = Mix_LoadWAV("sounds/Htsz1.wav");
	attack[HIT2] = Mix_LoadWAV("sounds/Htsz2.wav");
	attack[HIT3] = Mix_LoadWAV("sounds/Htsz3.wav");
	attack[HIT4] = Mix_LoadWAV("sounds/Htsz4.wav");
	attack[HIT5] = Mix_LoadWAV("sounds/MegaHtsz.wav");
}

void SoundPlayer::PlayWalk()
{
	int temp = rand() % 4;
	Mix_PlayChannel(-1, walk[temp], 0);
}

void SoundPlayer::PlayHitNormal()
{
	int temp = rand() % 4;
	Mix_PlayChannel(-1, attack[temp], 0);
}

void SoundPlayer::PlayHitHard()
{
	Mix_PlayChannel(-1, attack[HIT5], 0);
}

SoundPlayer::SoundPlayer()
{
	Init();
}

SoundPlayer::~SoundPlayer()
{
	std::cout << "Destroy audio player" << "\n";
	delete walk;
	delete attack;
	Mix_CloseAudio();
}
