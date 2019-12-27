#ifndef _MYBUTTON_H
#define _MYBUTTON_H

#include "glut.h"
#include <cstdio>
#include <vector>
using namespace std;
extern int g_window_width;
extern int g_window_height;

/*button function*/
extern int quit_btn;
extern int screenshot_button, obj_button;
class Button {
private:
	float m_fPosX;		//��ʾ������ͶӰ����ϵ(���½�Ϊ����ԭ��)�����꣬
	float m_fPosY;
	float m_fWidth;		//��Ļ���ص�λ
	float m_fHeight;
	int btn_id;
public:
	static int btn_count;
	bool m_bPressed;
	Button(){}
	void set(float posX, float posY, float width, float height);
	void Render();
	void OnMouseDown(float mousex, float mousey);
	void OnMouseUp();
	static int create(float posX, float posY);
};

extern vector<Button> Btn;

#endif