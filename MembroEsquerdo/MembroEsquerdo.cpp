#pragma comment(lib, "psmoveapi.lib")

#include "AbilityMapperHandler.h"

int main(int argc, char* argv[])
{
	AbilityMapperHandler handler;
	psmoveapi::PSMoveAPI api(&handler);

	while (true) {
		api.update();
	}

	return 0;
}