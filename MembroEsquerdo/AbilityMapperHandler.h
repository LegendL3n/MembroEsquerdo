#pragma once

#pragma comment(lib, "psmoveapi.lib")

#include "psmoveapi.h"
#include "MappedButton.h"
#include "DirectInputKeys.h"
#include "Utils.h"
#include <iostream>
#include <vector>

class AbilityMapperHandler : public psmoveapi::Handler
{
	void connect(Controller* controller);

	void update(Controller* controller);

	void disconnect(Controller* controller);

private:
	void handleButtonPress(Controller* controller);

	bool isButtonPressed(int buttons, PSMove_Button button);

	std::string getActiveWindowName();
};
