/*
 * GameRep.h
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#ifndef LIBS_REPOSITORIES_GAMEREPO_H_
#define LIBS_REPOSITORIES_GAMEREPO_H_

#include "../entities/GameEntity.h"

void gr_getGameById(GameEntity* gmLst, int gmLn, int gmId, GameEntity* gmEntAux);
void gr_showAGame(GameEntity gmEnt);
int gr_getGameIdByName(GameEntity* gmLst, int gmLn, char* gmName);

#endif /* LIBS_REPOSITORIES_GAMEREPO_H_ */
