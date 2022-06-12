#include "Utils.h"

int main() {
	Init();
	while (true) {
		Update(GetDeltaTime());
		Render();
	}
	Release();
	return 0;
}