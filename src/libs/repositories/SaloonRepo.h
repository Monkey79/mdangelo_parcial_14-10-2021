/*
 * SaloonRepo.h
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#ifndef LIBS_REPOSITORIES_SALOONREPO_H_
#define LIBS_REPOSITORIES_SALOONREPO_H_

#include "../entities/SaloonEntity.h"

void sr_initSaloonListHardCd(SaloonEntity* slLst,int from, int until);
int sr_initSaloonList(SaloonEntity* slLst, int slLn);

int sr_saveSaloon(SaloonEntity* slLst, int slLn, SaloonEntity slEnt, int frIdx);
int sr_getFreeSalonIndx(SaloonEntity* slLst, int slLn);

void sr_showASaloon(SaloonEntity slEnt);
void sr_showAllSaloon(SaloonEntity* slLst,int sLn);

void sr_getSaloonDescByType(int slType,char* slTypeStr);
void sr_getSaloonById(SaloonEntity* slLst,int sLn,int slId,SaloonEntity* slEntAux);
int sr_getSaloonIndxById(SaloonEntity* slLst,int sLn,int slId);
void sr_getSaloonNameById(SaloonEntity* slLst,int sLn,int slId,char* slName);

int sr_thereAreSaloons(SaloonEntity* slLst, int slLn);
int sr_isAValidSaloonId(SaloonEntity* slLst, int slLn, int slId);

#endif /* LIBS_REPOSITORIES_SALOONREPO_H_ */
