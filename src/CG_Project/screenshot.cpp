#include "project.h"

void screenshot::getBuffer(int width, int height, vector<unsigned char>& buf)
{
	vector<unsigned char> tmp_rgbdata(buf);
	for (int i = height - 1; i >= 0; i--)
	{
		memcpy(&buf[i * width * 3], &tmp_rgbdata[(height - i - 1) * width * 3], width * 3 * sizeof(unsigned char));
	}
	tmp_rgbdata.clear();
}

void screenshot::saveImg(struct tm* imageTime)
{
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	GLint xywh[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, xywh);
	vector<unsigned char> buf(xywh[2] * xywh[3] * 3);
	glReadPixels(xywh[0], xywh[1], xywh[2], xywh[3], GL_RGB, GL_UNSIGNED_BYTE, &buf[0]);
	getBuffer(xywh[2], xywh[3], buf);
	string h = to_string(imageTime->tm_hour);
	string m = to_string(imageTime->tm_min);
	string s = to_string(imageTime->tm_sec);
	string path = "screenshot\\Shot" + h + "_" + m + "_" + s + ".jpg";
	int save = SOIL_save_image
	(
		path.c_str(),
		SOIL_SAVE_TYPE_BMP,
		xywh[2], xywh[3], 3,
		&buf[0]
	);
	if (!save)  cout << "The image cannot be saved." << endl;
	else cout << "The image is saved." << endl;
}