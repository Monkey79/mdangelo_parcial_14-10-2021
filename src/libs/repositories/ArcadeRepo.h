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

int ar_getArcadeNmBySlId(ArcadeEntity* arLst, int arLn, int slId);

#endif /* LIBS_REPOSITORIES_ARCADEREPO_H_ */
