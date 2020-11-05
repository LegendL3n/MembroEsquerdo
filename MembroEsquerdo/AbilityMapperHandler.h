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
public:
	AbilityMapperHandler() : blink(false) {}

	void connect(Controller* controller);

	void update(Controller* controller);

	void disconnect(Controller* controller);

	bool blink;

private:
	void handleButtonPress(Controller* controller);

	void colorBattery(Controller* controller);

	bool isButtonPressed(int buttons, PSMove_Button button);

	std::string getActiveWindowName();
};
