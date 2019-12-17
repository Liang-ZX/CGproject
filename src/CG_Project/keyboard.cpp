#include "keyboard.h"

void key(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; break; }

	case ' ': {bAnim = !bAnim; break; }

	case 'a': {
		eye[0] += 0.1;
		center[0] += 0.1;
		break;
	}
	case 'd': {
		eye[0] += -0.1;
		center[0] += -0.1;
		break;
	}
	case 'w': {
		eye[1] += -0.1;
		center[1] += -0.1;
		break;
	}
	case 's': {
		eye[1] += 0.1;
		center[1] += 0.1;
		break;
	}
	case 'z': {
		eye[2] += -0.1;
		break;
	}
	case 'c': {
		eye[2] += 0.1;
		break;
	}
	}
}