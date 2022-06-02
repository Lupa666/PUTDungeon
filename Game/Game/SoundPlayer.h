#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>
#include <SDL_mixer.h>
#include <iostream>

typedef enum
{
	WALK1, WALK2, WALK3, WALK4
} WalkSound;

typedef enum
{
	HIT1, HIT2, HIT3, HIT4, HIT5
} AttackSound;


class SoundPlayer
{
private:
	void Init();
	Mix_Chunk *walk[4];
	Mix_Chunk *attack[5];

public:
	void PlayWalk();
	void PlayHitNormal();
	void PlayHitHard();
	SoundPlayer();
	~SoundPlayer();
};

