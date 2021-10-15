/*
 * SalonArcadeSrvc.h
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#ifndef LIBS_SERVICES_SALONARCADESRVC_H_
#define LIBS_SERVICES_SALONARCADESRVC_H_

#include "../repositories/ArcadeRepo.h"
#include "../repositories/GameRepo.h"
#include "../repositories/SaloonRepo.h"

int srv_initSaloonList(SaloonEntity* slList, int sLn);
int srv_initArcadeList(ArcadeEntity* arList, int aLn);

void srv_showSaloonExceedArc(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst,int arLn,int arcNm);

#endif /* LIBS_SERVICES_SALONARCADESRVC_H_ */
