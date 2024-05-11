#include "Snake.h"

using namespace std;

int main() {
	while (true) {
		SnakeGame sg(15, 20, 8, 150);
		sg.Play();
	}
	system("pause");
	return 0;
}