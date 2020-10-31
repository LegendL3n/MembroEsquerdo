#include "Utils.h"

void pressKey(WORD directKey)
{
		INPUT ip;

		ip.type = INPUT_KEYBOARD;
		ip.ki.time = 0;
		ip.ki.wVk = 0;
		ip.ki.dwExtraInfo = 0;

		// Hardware instead of a virtual keypress
		ip.ki.dwFlags = KEYEVENTF_SCANCODE;
		ip.ki.wScan = directKey;

		//Send the press
		SendInput(1, &ip, sizeof(INPUT));
}

void releaseKey(WORD directKey)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0;
	ip.ki.dwExtraInfo = 0;

	// Hardware instead of a virtual keypress
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	ip.ki.wScan = directKey;

	//Send the release
	SendInput(1, &ip, sizeof(INPUT));
}
