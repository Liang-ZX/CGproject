#include "stick.h"

int Stick::count = 0;

std::vector<Stick> StickVector;

int Stick::stickcreate(Sphere sp1, Sphere sp2)
{
	Stick tmp = Stick(count++, sp1, sp2);
	StickVector.push_back(tmp);
	return count - 1;
}