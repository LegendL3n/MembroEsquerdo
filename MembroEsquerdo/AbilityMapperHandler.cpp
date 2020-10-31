#include "AbilityMapperHandler.h"

const std::vector<MappedButton> usableButtons = {
	{ DIK_Q, 'Q', Btn_SQUARE, "Square" },
	{ DIK_W, 'W', Btn_TRIANGLE, "Triangle" },
	{ DIK_E, 'E', Btn_CROSS, "Cross" },
	{ DIK_R, 'R', Btn_CIRCLE, "Circle" },
	{ DIK_D, 'D', Btn_MOVE, "Move" },
	{ DIK_F, 'F', Btn_T, "T" },
	{ DIK_N, 'N', Btn_SELECT, "Select" },
};

const float TRIGGER_THRESHOLD = 0.8f;

void AbilityMapperHandler::connect(Controller* controller) {
	std::cout << "Connected: " << controller->serial << std::endl;

	int* last_press = new int(0);
	controller->user_data = last_press;
}

void AbilityMapperHandler::update(Controller* controller) {
	if (GetKeyState(VK_NUMLOCK) & 1) return;

	handleButtonPress(controller);
}

void AbilityMapperHandler::disconnect(Controller* controller) {
	std::cout << "Disconnect: %s\n" << controller->serial << std::endl;

	delete controller->user_data;
}

void AbilityMapperHandler::handleButtonPress(Controller* controller) {
	int* lastPressedButtons = (int*)controller->user_data;

	for (const MappedButton& btn : usableButtons) {
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

bool AbilityMapperHandler::isButtonPressed(int buttons, PSMove_Button button) {
	return (buttons & button) != 0;
}
