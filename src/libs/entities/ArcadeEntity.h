/*
 * ArcadeEntity.h
 *
 *  Created on: 15 oct. 2021
 *      Author: monkey
 */

#ifndef LIBS_ENTITIES_ARCADEENTITY_H_
#define LIBS_ENTITIES_ARCADEENTITY_H_

#include "../commons/Properties.h"

typedef struct{
	int arId; //AI
	char arNationality[STR_50];
	int arSoundType;  //1=Mono 2=Stereo
	int arPlayerAmount;
	int arCoinsCap;


	int arSlId; //fk
	int arGmId; //fk
	int arEmpty;
}ArcadeEntity;

#endif /* LIBS_ENTITIES_ARCADEENTITY_H_ */
