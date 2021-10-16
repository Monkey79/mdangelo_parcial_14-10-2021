/*
 * ArcadeRepo.h
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#ifndef LIBS_REPOSITORIES_ARCADEREPO_H_
#define LIBS_REPOSITORIES_ARCADEREPO_H_

#include "../entities/ArcadeEntity.h"

void ar_initArcadeListHardCd(ArcadeEntity* arLst, int from, int until);
int ar_initArcadeList(ArcadeEntity* arLst, int arLn);

void ar_showArcadeList(ArcadeEntity* arLst, int arLn);
void ar_showAnArcade(ArcadeEntity arcEnt);
void ar_showAnArcadeWithHisGame(ArcadeEntity arcEnt, char* gmDesc);

int ar_getArcadeAmountBySlId(ArcadeEntity* arLst, int arLn, int slId);
void ar_getArcadeBySaloonId(ArcadeEntity* arLst, int arLn, int slId, ArcadeEntity* arLstSal);
int ar_getArcadeCoinsCapacityBySaloonId(ArcadeEntity* arLst, int arLn, int slId);
int ar_getGameAmountInArcadeList(ArcadeEntity* arLst, int arLn, int gmId);

#endif /* LIBS_REPOSITORIES_ARCADEREPO_H_ */
