#ifndef _MATERIAL_H
#define _MATERIAL_H
typedef struct
{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess;
}MATERIAL;
#endif
