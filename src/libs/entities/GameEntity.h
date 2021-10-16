/*
 * GameEntity.h
 *
 *  Created on: 15 oct. 2021
 *      Author: monkey
 */

#ifndef LIBS_ENTITIES_GAMEENTITY_H_
#define LIBS_ENTITIES_GAMEENTITY_H_

#include "../commons/Properties.h"

typedef struct{
	int gmId;
	char gmDesc[STR_63];
	int gmEmpty;
}GameEntity;

#endif /* LIBS_ENTITIES_GAMEENTITY_H_ */
