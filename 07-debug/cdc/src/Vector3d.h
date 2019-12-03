/*
 * Vector3d.h
 *
 *  Created on: Jul 26, 2009
 *      Author: ghaitho
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

struct Vector3dType;

typedef struct Vector3dType
{
    float x;
    float y;
    float z;
} Vector3d ;

void VECTOR3D_init(Vector3d *);
void VECTOR3D_init2(Vector3d * v,float i, float j, float k);
void VECTOR3D_set(Vector3d * v,float i, float j, float k);
int VECTOR3D_hashCode(Vector3d * v);
char * VECTOR3D_toString(char * buf, Vector3d * v);

#endif /* VECTOR3D_H_ */
