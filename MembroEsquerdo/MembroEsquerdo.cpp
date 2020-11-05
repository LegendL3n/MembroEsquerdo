#pragma comment(lib, "psmoveapi.lib")

#include "AbilityMapperHandler.h"

#include <chrono>

using namespace std::chrono;

long getCurrentMs() {
	return duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		).count();
}

int main(int argc, char* argv[])
{
	AbilityMapperHandler handler;
	psmoveapi::PSMoveAPI api(&handler);

	long lastBlink = getCurrentMs();

	while (true) {
		if (getCurrentMs() - lastBlink > 500) {
			handler.blink = !handler.blink;

			lastBlink = getCurrentMs();
		}

		api.update();

		psmove_util_sleep_ms(2);
	}

	return 0;
}