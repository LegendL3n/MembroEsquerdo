#pragma once
#pragma comment(lib, "psmoveapi.lib")

#include "psmoveapi.h"

#include <Windows.h>
#include <string>

struct MappedButton {
	WORD directInputKey;
	CHAR key;

	PSMove_Button moveBtn;
	std::string moveBtnStr;
};
