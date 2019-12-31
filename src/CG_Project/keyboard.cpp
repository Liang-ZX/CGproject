#include "keyboard.h"
#include "CollisionDetection.h"
#define LIGHT_STEP  1
extern Light light[8];
extern GLint light_cur;
void key(unsigned char k, int x, int y)
{
	if (gameState == MAINWINDOW)
	{
		switch (k)
		{
		case 27:
		case 'q': {exit(0); break; }
		case 'p': {bPersp = !bPersp; break; }

		case ' ': {bAnim = !bAnim; break; }

		case 'a': {
			if (isLegalToMoveView()) {
				eye[0] += 0.1;
				center[0] += 0.1;
			}
			else {
				eye[0] += -0.1;
				center[0] += -0.1;
			}
			break;
		}
		case 'd': {
			if (isLegalToMoveView()) {
				eye[0] += -0.1;
				center[0] += -0.1;
			}
			else {
				eye[0] += 0.1;
				center[0] += 0.1;
			}
			break;
		}
		case 'w': {
			if (isLegalToMoveView()) {
				eye[1] += -0.1;
				center[1] += -0.1;
			}
			else {
				eye[1] += 0.1;
				center[1] += 0.1;
			}
			
			break;
		}
		case 's': {
			if (isLegalToMoveView()) {
				eye[1] += 0.1;
				center[1] += 0.1;
			}
			else {
				eye[1] += -0.1;
				center[1] += -0.1;
			}
			break;
		}
		case 'z': {
			if (isLegalToMoveView())
				eye[2] += -0.1;
			else
				eye[2] += 0.1;
			break;
		}
		case 'c': {
			if (isLegalToMoveView())
				eye[2] += 0.1;
			else 
				eye[2] += -0.1;
			break;
		}
		case 'f': {
			time_t ttime;
			struct tm* image;
			time(&ttime);
			image = localtime(&ttime);
			screenshot::saveImg(image);
		}
		// change the position of Light:
				case 'i': {
			light[light_cur].changePosition(0, LIGHT_STEP, 0); break;
		}
				case 'k': {
					light[light_cur].changePosition(0, -LIGHT_STEP, 0); break;
				}
				case 'j': {
					light[light_cur].changePosition(-LIGHT_STEP,0, 0); break;
				}
				case 'l': {
					light[light_cur].changePosition(LIGHT_STEP,0, 0); break;
				}
				case 'm': {
					light[light_cur].changePosition( 0, 0,LIGHT_STEP); break;
				}
				case ',': {
					light[light_cur].changePosition(0, 0, -LIGHT_STEP); break;
				}

		}
	}
}