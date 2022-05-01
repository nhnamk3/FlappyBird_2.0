#include "PipeDouble.h"
PipeDouble::PipeDouble()
{
	srand(time(NULL));
	p_pipe_top = new Pipe;
	p_pipe_bot = new Pipe;
	velocity_ = 150;
	time_ = 0;
}
PipeDouble::~PipeDouble()
{
	delete p_pipe_top;
	delete p_pipe_bot;
}
Pipe* PipeDouble::GetPipeTop()
{
	if (p_pipe_top != NULL) return p_pipe_top;
}
Pipe* PipeDouble::GetPipeBot()
{
	if (p_pipe_bot != NULL)	return p_pipe_bot;
}
void PipeDouble::HandleMove(const int& x_size)
{
	time_ += deltaTime;
	SDL_Rect rect_top = p_pipe_top->GetRect();
	SDL_Rect rect_bot = p_pipe_bot->GetRect();
	int x = rect_top.x;
	int w = rect_top.w;
	int h = rect_top.h;
	int y_top = rect_top.y;
	int y_bot = rect_bot.y;
	double limitTime = static_cast<double>((x_size + PIPE_WIDTH)) / velocity_;
	if (time_ > limitTime) {
		x = x_size;
		time_ = 0;
		int ranNum = GetRand(0, 250);
		p_pipe_top->SetRect(x_size, -ranNum);
		p_pipe_bot->SetRect(x_size, -ranNum + PIPE_DISTANCE + PIPE_HEIGHT);
	}
	else {
		x = x_size - velocity_ * time_;
		p_pipe_top->SetRect(x, y_top);
		p_pipe_bot->SetRect(x, y_bot);
	}
}
int PipeDouble::GetRand(int low, int high)
{
	return rand() % (high - low + 1) + low;;
}