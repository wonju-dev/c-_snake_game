#include "Utils.h"

int maxwidth;
int maxHeight;

int main() {
	Init();
	while (true) {
		Update(GetDeltaTime());
		Render();
	}
	Release();
	return 0;
}