/*
 * SalonArcadeSrvc.c
 * Created on: 15 oct. 2021
 * Author: mdangelo
 */


#include "../commons/StringUtils.h"
#include "../commons/NumberUtils.h"
#include "SalonArcadeSrvc.h"

#define SALON_CREAT_CANCEL "-creacion salon cancelada-\n"
#define SALOON_CREATE_SUCCESS "-creacion salon exitosa-\n"
#define NO_SALOON_SPACE "-No hay mas espacion en la lista de salones-\n"
#define SALOON_LIST_EMPTY "--No hay ningun salon, la lista esta vacia--\n"

#define ERROR_ABM "-hubo un error-"

#define NO_ARCADE_SPACE "-NO hay espacio en la lista de arcades-\n"
#define ARCADE_LIST_EMPTY "-La lista de arcades esta vacia-\n"
#define ARCADE_CREATE_SUCCESS "-creacion arcade exitosa-\n"
#define ARCADE_CREATE_CANCEL "-creacion arcade cancelada-\n"
#define ARCADE_UPDATE_CANCEL "-actualizacion arcade cancelada-\n"
#define ARCADE_UPDATE_SUCCESS "-actualizacion arcade exitosa-\n"
#define ARCADE_DELETE_SUCCESS "-eliminacion arcade exitosa-\n"
#define ARCADE_DELETE_CANCEL "-eliminacion arcade cancelada-\n"





int srv_initSaloonList(SaloonEntity* slList, int sLn){
	return sr_initSaloonList(slList, sLn);
}

int srv_initArcadeList(ArcadeEntity* arList, int aLn){
	return ar_initArcadeList(arList, aLn);
}


//---Abms
void srv_createSaloon(SaloonEntity* slLst, int slLn, int* slId){
	char qst;
	int rslt; //resultado de la creacion

	int freeIdx = sr_getFreeSalonIndx(slLst, slLn);

	if(freeIdx>=0){
		SaloonEntity slEnt;
		str_getStringInput(slEnt.slName, STR_50, "-ingrese nombre del salon-");
		str_cleanString(slEnt.slName, STR_50);
		str_getStringInput(slEnt.slAddress, STR_50, "-ingrese direccion del salon-");
		str_cleanString(slEnt.slAddress, STR_50);

		do{
			slEnt.slType = nmb_getInputByRank("-ingrese tipo de salon [1=Shoping 2=Local]-", 1, 2);
		}while(slEnt.slType!=1 && slEnt.slType!=2);

		do{
			qst = str_getYesNoQstion("-desea crear este salon?[S|N]-");
		}while(qst!='S' && qst!='N');

		if(qst == 'S'){
			slEnt.slId = ++(*slId);
			slEnt.slEmpty = FALSE;
			rslt = sr_saveSaloon(slLst, slLn, slEnt, freeIdx);
			if(rslt){
				printf(SALOON_CREATE_SUCCESS);
				sr_showAllSaloon(slLst,slLn);
			}else{
				printf(ERROR_ABM);
			}
		}else{
			printf(SALON_CREAT_CANCEL);
		}
	}else{
		printf(NO_SALOON_SPACE);
	}


}

void srv_deleteSaloonById(SaloonEntity* slLst, int slLn,ArcadeEntity* arList,int arLn){
	char qst;
	int rslt; //resultado de la eliminacion

	int areSls = sr_thereAreSaloons(slLst, slLn);
	int i;

	if(areSls){
		//hay algo para eliminar
		sr_showAllSaloon(slLst, slLn);
		i = nmb_getIntInput("-ingrese el id del salon a eliminar-");
		rslt = sr_deleteSaloonById(slLst, slLn, i);
		if(rslt){
			//eliminacio exitosa (se elminara todos los arcades asociados)
			rslt = ar_deleteArcadesBySaloonId(arList, arLn, i);
			//if(!rslt) printf(ERROR_ABM);
		}else
			printf(ERROR_ABM);
	}else{
		//no hay ningun salon creadon para eliminar
		printf(SALOON_LIST_EMPTY);
	}
}

void srv_showAllSaloons(SaloonEntity* slLst, int slLn){
	if(sr_thereAreSaloons(slLst, slLn)){
		sr_showAllSaloon(slLst, slLn);
	}else
		printf(SALOON_LIST_EMPTY);
}


void srv_createArcade(ArcadeEntity* arList, int arLn, SaloonEntity* slLst, int slLn, GameEntity* gmLst, int gmLn,int* arId){
	int arcIdx = ar_getFreeArcadeIndx(arList, arLn); //indice espacio libre [-1 si no hay espacio libre]
	int salsExist = sr_thereAreSaloons(slLst, slLn);

	char gmName[STR_63];
	int gmId;
	char qst;
	int rstl;

	if(arcIdx>=0 && salsExist){
		//hay espacio en la lista de arcades y existen salones para asignar

		ArcadeEntity arcEnt;
		str_getStringInput(arcEnt.arNationality, STR_50, "-ingrese la nacionalidad del arcade-");
		str_cleanString(arcEnt.arNationality, STR_50);
		arcEnt.arSndTp = nmb_getInputByRank("-ingrese tipo de sonido del arcade [1=Stereo 2=Mono]-", 1, 2);
		arcEnt.arPlyAmt = nmb_getIntInput("-ingrese cantidad de jugadores-");
		arcEnt.arCoinsCap = nmb_getIntInput("-ingrese la capacidad de fichas-");

		do{
			sr_showAllSaloon(slLst, slLn);
			arcEnt.arSlId = nmb_getIntInput("-ingrese un id de salon valido-");
		}while(!sr_isAValidSaloonId(slLst, slLn, arcEnt.arSlId));

		do{
			gr_showAllGames(gmLst, gmLn);
			str_getStringInput(gmName, STR_63, "-del listado de juegos ingrese un nombre valido-");
			str_cleanString(gmName, STR_63);
			gmId = gr_getGameIdByName(gmLst, gmLn, gmName); //id de juego segun nombre (-1 si no hay id que haga match con nombre)
		}while(gmId ==-1);
		arcEnt.arGmId = gmId;

		do{
			qst = str_getYesNoQstion("-desea incorporar este arcade?[S|N]-");
		}while(qst!='S' && qst!='N');

		if(qst=='S'){
			arcEnt.arId = ++(*arId);
			arcEnt.arEmpty = FALSE;
			rstl = ar_saveArcade(arList, arLn, arcEnt, arcIdx);
			if(rstl){
				printf(ARCADE_CREATE_SUCCESS);
				ar_showAnArcadeWithHisGame(arcEnt, gmName);
			}else
				printf(ERROR_ABM);
		}else{
			printf(ARCADE_CREATE_CANCEL);
		}

	}else{
		printf("-=================-\n");
		printf(NO_ARCADE_SPACE);
		printf("\t y/o \n");
		printf(SALOON_LIST_EMPTY);
		printf("-=================-\n");
	}
}

void srv_updateArcade(ArcadeEntity* arList, int arLn, GameEntity* gmList, int gmLn){
	ArcadeEntity arcEnt;
	arcEnt.arEmpty = TRUE;

	int arcId;
	int gmId;
	char qst;
	int rstl;
	char gmName[STR_63];

	if(ar_thereAreArcades(arList, arLn)){

		//de la lista de arcades, elige un id valido
		do{
			ar_showArcadeList(arList, arLn);
			arcId = nmb_getIntInput("-ingrese un id de arcade valido-\n");
			ar_getArcadeById(arList, arLn, arcId, &arcEnt);
		}while(arcEnt.arEmpty);


		arcEnt.arPlyAmt = nmb_getIntInput("--ingrese cantidad de jugadores--");

		do{
			gr_showAllGames(gmList, gmLn);
			str_getStringInput(gmName, STR_63, "-del listado de juegos ingrese un nombre valido-");
			str_cleanString(gmName, STR_63);
			gmId = gr_getGameIdByName(gmList, gmLn, gmName); //id de juego segun nombre (-1 si no hay id que haga match con nombre)
		}while(gmId ==-1);

		do{
			qst = str_getYesNoQstion("--desea actualizar esta arcade? [S|N]--");
		}while(qst!='S' && qst!='N');


		if(qst=='S'){
			arcEnt.arGmId = gmId;
			rstl = ar_updateArcade(arList, arLn, arcEnt);
			if(rstl){
				printf(ARCADE_UPDATE_SUCCESS);
				ar_showArcadeList(arList, arLn);
			}
		}else{
			printf(ARCADE_UPDATE_CANCEL);
		}
	}else{
		printf(ARCADE_LIST_EMPTY);
	}
}

void srv_deleteArcade(ArcadeEntity* arList, int arLn,SaloonEntity* slList, int slLn, GameEntity* gmList, int gmLn){
	char slName[STR_50];
	char gmName[STR_63];

	int arcId;
	int arIdx;
	char qst;
	int rslt;

	if(ar_thereAreArcades(arList, arLn)){
		do{
			ar_showArcadeList(arList, arLn);
			arcId = nmb_getIntInput("--del listado de arcades seleccione un id valido a eliminar--");
			arIdx = ar_getIndxFromArcId(arList, arLn, arcId); //[-1 si indice no existe para ese id]
		}while(arIdx == -1);

		do{
			qst = str_getYesNoQstion("--desea eliminar el arcade [S|N]--?");
		}while(qst!='S' && qst!='N');

		if(qst=='S'){
			rslt = ar_deleteArcadeByIndx(arList, arLn, arIdx);
			if(rslt) printf(ARCADE_DELETE_SUCCESS);
			ar_showArcadeList(arList, arLn);
		}else{
			printf(ARCADE_DELETE_CANCEL);
		}

	}else{
		printf(ARCADE_LIST_EMPTY);
	}
}

void srv_showAllArcadesComplete(ArcadeEntity* arList, int arLn, SaloonEntity* slList, int slLn, GameEntity* gmLst, int gmLn){
	ArcadeEntity arcEnt;
	char gmName[STR_63];
	char slName[STR_50];
	char soundTp[STR_50];

	for(int i=0;i<arLn; i++){

		if(!(arList+i)->arEmpty){
			arcEnt = *(arList+i);
			gr_getGameNameById(gmLst, gmLn, (arList+i)->arGmId, gmName);  //obtengo nombre del juego por id
			sr_getSaloonNameById(slList, slLn, (arList+i)->arSlId, slName);//objengo nombre del salon por id

			ar_getSoundTypeDescById((arList+i)->arSndTp,soundTp);
			printf("-arc.id=%d | arc.nacionalidad=%s | arc.tipo_sonido=%s | arc.cant_jug=%d | arc.capacidad_fichas=%d | arc.salon_nombre=%s | arc.game_nombre=%s\n",
					(arList+i)->arId,(arList+i)->arNationality,soundTp,(arList+i)->arPlyAmt, (arList+i)->arCoinsCap, slName, gmName);
		}
	}
}

void srv_showAllGamesInArcades(ArcadeEntity* arList, int arLn, GameEntity* gmLst, int gmLn){
	printf("--los siguientes juegos estan en todos los arcades--\n");
	for(int i=0; i<gmLn; i++){
		if(!(gmLst->gmEmpty)){
			if(ar_isGameInArcadeList(arList, arLn, (gmLst+i)->gmId)){
				gr_showAGame(*(gmLst+i));
			}
		}

	}
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
