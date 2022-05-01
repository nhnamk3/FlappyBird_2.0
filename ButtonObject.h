#pragma once
#include "BaseObject.h"
class ButtonObject : public BaseObject
{
public:
	ButtonObject();
	~ButtonObject();
	void Update();
	void Handle();
private:
	bool isSelected_;
};