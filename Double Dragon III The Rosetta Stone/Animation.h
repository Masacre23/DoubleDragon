#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

private:
	float current_frame;
	bool finished = false;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		finished = false;
		if (current_frame >= frames.size())
		{
			current_frame = 0.0f;
			finished = true;
		}
		return frames[(int)current_frame];
	}

	bool AnimationFinished()
	{
		if (finished)
		{
			finished = false;
			current_frame = 0.0f;
			return true;
		}
		return false;
	}
};