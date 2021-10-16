/*
 * SalonArcadeSrvc.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */

#include "SalonArcadeSrvc.h"
#include "../commons/StringUtils.h"
#include "../commons/NumberUtils.h"

int srv_initSaloonList(SaloonEntity* slList, int sLn){
	return sr_initSaloonList(slList, sLn);
}

int srv_initArcadeList(ArcadeEntity* arList, int aLn){
	return ar_initArcadeList(arList, aLn);
}


//----Informes

void srv_showSaloonExceedArc(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst,int arLn,int arcNm){
	int arcAmnt=0; //cant de arcades por salon
	int cnt=0;
	int hit=0;

	for(int i=0;i<sLn;i++){
		if(!(slLst+i)->slEmpty){
			hit++;
			arcAmnt = ar_getArcadeAmountBySlId(arLst, arLn, (slLst+i)->slId);
			if(arcAmnt > arcNm){
				sr_showASaloon(*(slLst+i));
			}else if(arcAmnt==0)
				printf("-el salon %s no tiene arcades asignados-\n",(slLst+i)->slName);
			else
				cnt++;
		}
	}
	if(hit==cnt) printf("-no hubo ningun salon que supere la cantidad de %d arcades-\n",arcNm);
}

void srv_showArcadeMorePlayerThan(SaloonEntity* slLst,int sLn,ArcadeEntity* arLst, int arLn, int arcPlyNm, GameEntity* gmLst, int gmLn){
	ArcadeEntity arcEntAux; //arcade que supera la cant
	arcEntAux.arEmpty = TRUE;
	SaloonEntity slEntAux;
	slEntAux.slEmpty = TRUE;
	GameEntity gmEntAux;
	gmEntAux.gmEmpty = TRUE;

	int hit=0;
	int cont=0;

	for(int i=0;i<arLn;i++){
		if(!(arLst+i)->arEmpty){
			hit++;
			arcEntAux = *(arLst+i);
			if(arcEntAux.arPlyAmt > arcPlyNm){
				sr_getSaloonById(slLst, sLn, arcEntAux.arSlId, &slEntAux);
				gr_getGameById(gmLst, gmLn, arcEntAux.arGmId, &gmEntAux);

				printf("-arcade que supera la cantidad de %d jugadores: arc.id=%d | arc.cant_jug=%d | arc.jug_nombre=%s | arc.salon=%s\n"
						,arcPlyNm,arcEntAux.arId,
						arcEntAux.arPlyAmt, gmEntAux.gmDesc,
						slEntAux.slName);

			}else
				cont++;
		}
	}
	if(hit==cont) printf("-NO hubo ningun arcade que supera la cantidad de %d jugadores-\n",arcPlyNm);
}

void srv_showSaloonInfo(SaloonEntity* slList,int slLn, ArcadeEntity* arLst, int arLn) {
	int slId = nmb_getIntInput("-ingrese el id del salon-\n");
	int arNm = 0; //cant arcades que posee un salon

	SaloonEntity slEntAux;
	slEntAux.slEmpty = TRUE;
	sr_getSaloonById(slList, slLn, slId, &slEntAux);

	if(!slEntAux.slEmpty){
		sr_showASaloon(slEntAux);
		arNm = ar_getArcadeAmountBySlId(arLst, arLn, slEntAux.slId);
		if(arNm>0) printf("\t ->este salon posee %d arcades-\n", arNm);
	}else
		printf("-No se encontro salon con ese id-\n");
}

void srv_showArcadeAndGameInfoBySalonId(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn,GameEntity* gmList,int gmLN) {
	int slId = nmb_getIntInput("-ingrese el id del salon-\n");

	SaloonEntity slEntAux;
	slEntAux.slEmpty = TRUE;
	sr_getSaloonById(slList, slLn, slId, &slEntAux);

	GameEntity gmEntAux;
	gmEntAux.gmEmpty = TRUE;

	if(!(slEntAux.slEmpty)){
		printf("\t->el salon :\n");
		sr_showASaloon(slEntAux);
		printf("\t->tiene los arcades:\n");

		for(int i=0;i<arLn;i++){
			if(!(arList+i)->arEmpty){
				if((arList+i)->arSlId == slEntAux.slId){
					gr_getGameById(gmList,gmLN,(arList+i)->arGmId,&gmEntAux);
					if(!gmEntAux.gmEmpty){
						ar_showAnArcadeWithHisGame(*(arList+i), gmEntAux.gmDesc);
					}else
						printf("-este arcade no tiene asignado ningun juego-\n");
				}
			}
		}
	}else{
		printf("-No se encontro salon con ese id-\n");
	}
}

void srv_showSaloonWithMaxArcade(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn){
	int arMx=0;
	int arNm;
	SaloonEntity slEntMax;

	for(int i=0; i<slLn; i++) {
		if(!(slList+i)->slEmpty){
			arNm = ar_getArcadeAmountBySlId(arList, arLn, (slList+i)->slId);
			if(arNm > arMx){
				arMx = arNm;
				slEntMax = *(slList+i);
			}
		}
	}
	printf("-el salon con mas cantidad de arcades es->");
	sr_showASaloon(slEntMax);
	printf("-con la cantidad de %d arcades \n",arMx);
}

void srv_showSaloonIncome(SaloonEntity* slList,int slLn,ArcadeEntity* arList,int arLn){
	int slId = nmb_getIntInput("-ingrese el id del salon-");
	float coinPrice = nmb_getFloatInput("-ingrese precio de la ficha-");
	int coins = 0;

	SaloonEntity slEntAux;
	slEntAux.slEmpty = TRUE;
	sr_getSaloonById(slList, slLn, slId, &slEntAux);

	if(!slEntAux.slEmpty){
		coins = ar_getArcadeCoinsCapacityBySaloonId(arList,arLn, slEntAux.slId);
		if(coins>0)
			printf("-el salon.nombre=%s recaudaria una cantidad de $%.2f-\n",slEntAux.slName,(float)(coinPrice*coins));
	}else{
		printf("-No se encontro salon con ese id-\n");
	}
}

void srv_showAmountGameInArcades(ArcadeEntity* arList,int arLn, GameEntity* gmLst, int gmLn){
	char gameName[STR_63];
	str_getStringInput(gameName, STR_63, "-ingrese el nombre del juego-");
	str_cleanString(gameName, STR_63);

	int gmId = gr_getGameIdByName(gmLst, gmLn, gameName);
	int arcCnt=0;

	printf("-->evaluar juego.nombre %s juego.id %d-\n", gameName, gmId);
	if(gmId>0){
		arcCnt = ar_getGameAmountInArcadeList(arList, arLn, gmId);
		printf("-el juego %s esta en %d arcades-\n", gameName, arcCnt);
	}else{
		printf("-NO se encontro juego con ese nombre-\n");
	}
}
//------Private
