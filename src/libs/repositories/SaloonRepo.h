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

void sr_showASaloon(SaloonEntity slEnt);
void sr_getSaloonDescByType(int slType,char* slTypeStr);
void sr_getSaloonById(SaloonEntity* slLst,int sLn,int slId,SaloonEntity* slEntAux);


#endif /* LIBS_REPOSITORIES_SALOONREPO_H_ */
