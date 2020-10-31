#pragma once

#include "MappedButton.h"

#include <psmoveapi.h>
#include <vector>

struct Mode
{
	RGB ledColor;
	std::vector<MappedButton> mappedButtons;
};
