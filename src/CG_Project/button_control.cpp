#include"project.h"
//quit_button
extern int gameState;

//analize the button state and do the proper actions
void button_control() {
	if (Btn[quit_btn].m_bPressed)
		gameState = GAMEEND;
	if (Btn[screenshot_button].m_bPressed) {
		time_t ttime;
		struct tm* image;
		time(&ttime);
		image = localtime(&ttime);
		screenshot::saveImg(image);
	}
	if (Btn[obj_button].m_bPressed) {
		;
	}
}