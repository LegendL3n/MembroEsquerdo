#include "AbilityMapperHandler.h"
#include "Mode.h"
#include "ColorConverter.h"

#include <map>

const std::map<std::string, Mode> modes = {
	{
		"League of Legends (TM) Client", {
			{ 0, 34, 8 },
			{
				{ DIK_Q, 'Q', Btn_SQUARE, "Square" },
				{ DIK_W, 'W', Btn_TRIANGLE, "Triangle" },
				{ DIK_E, 'E', Btn_CROSS, "Cross" },
				{ DIK_R, 'R', Btn_CIRCLE, "Circle" },
				{ DIK_D, 'D', Btn_MOVE, "Move" },
				{ DIK_F, 'F', Btn_T, "T" },
				{ DIK_N, 'N', Btn_SELECT, "Select" },
				{ DIK_Y, 'Y', Btn_START, "Start" },
			}
		}
	},
	{
		"osu!", {
			{ 123, 0, 123 },
			{
				{ DIK_X, 'X', Btn_SQUARE, "Square" },
				{ DIK_X, 'X', Btn_TRIANGLE, "Triangle" },
				{ DIK_Z, 'Z', Btn_CROSS, "Cross" },
				{ DIK_Z, 'Z', Btn_CIRCLE, "Circle" },
			}
		}
	}
};

const float TRIGGER_THRESHOLD = 0.8f;

void AbilityMapperHandler::connect(Controller* controller) {
	std::cout << "Connected: " << controller->serial << std::endl;

	int* last_press = new int(0);
	controller->user_data = last_press;
}

void AbilityMapperHandler::update(Controller* controller) {
	handleButtonPress(controller);

	colorBattery(controller);
}

void AbilityMapperHandler::disconnect(Controller* controller) {
	std::cout << "Disconnect: %s\n" << controller->serial << std::endl;

	delete controller->user_data;
}

void AbilityMapperHandler::handleButtonPress(Controller* controller) {
	int* lastPressedButtons = (int*)controller->user_data;

	std::string wndName = getActiveWindowName();

	if (wndName != "") {
		Mode currentMode;
		bool found = false;

		for (std::pair<std::string, Mode> mode : modes) {
			if (wndName.rfind(mode.first, 0) == 0) {
				currentMode = mode.second;
				found = true;
			}
		}

		if (found) {
			for (const MappedButton& btn : currentMode.mappedButtons) {
				if (!isButtonPressed(*lastPressedButtons, btn.moveBtn) && isButtonPressed(controller->buttons, btn.moveBtn)) {
					if (btn.moveBtn == Btn_T && controller->trigger < TRIGGER_THRESHOLD) continue;

					pressKey(btn.directInputKey);
					std::cout << btn.moveBtnStr << "(" << btn.key << ") Pressed" << std::endl;

					*lastPressedButtons |= btn.moveBtn;
				}

				if (isButtonPressed(*lastPressedButtons, btn.moveBtn) && !isButtonPressed(controller->buttons, btn.moveBtn)) {
					releaseKey(btn.directInputKey);
					std::cout << btn.moveBtnStr << "(" << btn.key << ") Released" << std::endl;

					*lastPressedButtons &= ~btn.moveBtn;
				}
			}
		}
		else {
			controller->color = { 0, 0, 0 };
		}
	}
}

void AbilityMapperHandler::colorBattery(Controller* controller)
{
	Palette::HSV colorGen(5, 1.0, (blink || controller->battery > Batt_20Percent) ? 0.01 + controller->battery * 0.02 : 0.f);

	switch (controller->battery) {
	case (Batt_CHARGING):
		break;
	case (Batt_CHARGING_DONE):
		break;
	default:
		controller->color = colorGen.toRGB();
	}
}

bool AbilityMapperHandler::isButtonPressed(int buttons, PSMove_Button button) {
	return (buttons & button) != 0;
}

std::string AbilityMapperHandler::getActiveWindowName()
{
	HWND foreground = GetForegroundWindow();

	if (foreground)
	{
		char windowTitle[256];
		GetWindowTextA(foreground, windowTitle, 256);

		return std::string(windowTitle);
	}

	return std::string();
}
