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

//--Informes
void srv_showSaloonExceedArc(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst,int arLn,int arcNm);
void srv_showArcadeMorePlayerThan(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst,int arLn,int arcPlyNm, GameEntity* gmLst, int gmLn);
void srv_showSaloonInfo(SaloonEntity* slList,int slLn, ArcadeEntity* arLst, int arLn);
void srv_showArcadeAndGameInfoBySalonId(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn,GameEntity* gmList,int gmLN);
void srv_showSaloonWithMaxArcade(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn);
void srv_showSaloonIncome(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn);
void srv_showAmountGameInArcades(ArcadeEntity* arList,int arLn, GameEntity* gmLst, int gmLn);

#endif /* LIBS_SERVICES_SALONARCADESRVC_H_ */
