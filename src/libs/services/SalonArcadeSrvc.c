/*
 * SalonArcadeSrvc.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include "SalonArcadeSrvc.h"

int srv_initSaloonList(SaloonEntity* slList, int sLn){
	return sr_initSaloonList(slList, sLn);
}

int srv_initArcadeList(ArcadeEntity* arList, int aLn){
	return ar_initArcadeList(arList, aLn);
}


//----Informes
void srv_showSaloonExceedArc(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst,int arLn,int arcNm){
	int slArcNmMx=arcNm;
	int slArcNmAux=0;

	for(int i=0;i<sLn;i++){
		if(!(slLst+i)->slEmpty){
			slArcNmAux = ar_getArcadeNmBySlId(arLst, arLn, (slLst+i)->slId);
			if(slArcNmAux > arcNm){
				sr_showASaloon(*(slLst+i));
			}
			slArcNmAux = 0;
		}
	}
}
