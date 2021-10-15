/*
 * SaloonEntity.h
 *
 *  Created on: 15 oct. 2021
 *      Author: monkey
 */

#ifndef LIBS_ENTITIES_SALOONENTITY_H_
#define LIBS_ENTITIES_SALOONENTITY_H_

#include "../commons/Properties.h"

typedef struct{
	int slId; //AI
	char slName[STR_50];
	char slAddress[STR_50];
	int slType; //1=Shoping 2=Local

	int slEmpty;
}SaloonEntity;


#endif /* LIBS_ENTITIES_SALOONENTITY_H_ */
