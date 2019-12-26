#include "button.h"
#include <vector>
using namespace std;

vector<Button> Btn;
int Button::btn_count = 0;

int quit_btn;
int screenshot_button, obj_button;

int Button::create(float posX, float posY)
{
	Button newbtn;
	newbtn.set(posX, posY, 10, 2);
	Btn.push_back(newbtn);
	newbtn.btn_id = btn_count++;
	return newbtn.btn_id;
}

void Button::set(float posX, float posY, float width, float height)
{
	this->m_bPressed = false;
	this->m_fPosX = posX;
	this->m_fPosY = posY;
	this->m_fWidth = width;
	this->m_fHeight = height;
}

void Button::Render()
{
	GLfloat box_whratio = 0.15*g_window_width / g_window_height;
	m_fHeight = m_fWidth * box_whratio / 5;
	glPushMatrix();
	glLoadIdentity();
	//将中心位于原点的cube移动到使cube左下角坐标为m_fPosX,m_fPosY的位置
	//必须考虑cube的自身长宽
	glTranslatef(m_fPosX + m_fWidth / 2, m_fPosY + m_fHeight / 2, 0.0);
	if (m_bPressed)
	{
		//double scaleAmt = 10.0 * sin( (double)rand() );
		//double scaleAmt = sin( (double)rand() );
		glScalef(0.9, 0.9, 1.0);
	}
	//cube中心位于原点
	glScalef(m_fWidth, m_fHeight, 1.0);
	glColor3f(192.0 / 255, 192.0 / 255, 192.0 / 255);
	glutSolidCube(1.0);
	glPopMatrix();
}
void Button::OnMouseDown(float mousex, float mousey)
{
	mousey = 10 - mousey;
	if (mousex > m_fPosX && mousex < m_fPosX + m_fWidth &&
		mousey > m_fPosY && mousey < m_fPosY + m_fHeight)
	{
		m_bPressed = true;
	}
	return;
}
void Button::OnMouseUp()
{
	m_bPressed = false;
}