#pragma once
#include "Pipe.h"
#include <cstdlib>
class PipeDouble : public Pipe
{
public:
	PipeDouble();
	~PipeDouble();
	Pipe* GetPipeTop();
	Pipe* GetPipeBot();
	void HandleMove(const int& x_size);
	int GetRand(int low, int high);
private:
	Pipe* p_pipe_top;
	Pipe* p_pipe_bot;
	int velocity_;
	double time_;
};