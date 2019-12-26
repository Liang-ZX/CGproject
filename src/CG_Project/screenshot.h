#pragma once

static class screenshot
{
public:
	static void getBuffer(int width, int height, vector<unsigned char>& buf);
	//utilize tm from time 
	static void saveImg(struct tm* imageTime);
};