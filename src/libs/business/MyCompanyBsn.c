/*
 * MyCompany.c
 * Created on: 14 oct. 2021
 * Author: mdangelo
 */

#include <stdio.h>
#include <ctype.h>

#include "../commons/Properties.h"
#include "../commons/StringUtils.h"
#include "../commons/NumberUtils.h"

#include "MyCompanyBsn.h"
#include "../services/SalonArcadeSrvc.h"

//---Const
#define GAME_TOP 100
#define SALON_TOP 100
#define ARCADE_TOP 1000

void _checkUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int usrSlct,int *slId, int *arId);
void _createShowReportsMenu(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList);
void _checkReportUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int rpUsrSlc);

void bsn_startMyCompanyApp(void){
	int slId=8; //ultimo id creado
	int arId=16;
	int debug = FALSE;

	GameEntity gmList[GAME_TOP] = {{1,"game_1",FALSE},
								   {2,"game_2",FALSE},
								   {3,"game_3",FALSE},
								   {4,"game_4",FALSE},
								   {5,"game_5",FALSE},
								   {6,"game_6",FALSE}};

	/*SaloonEntity slList[SALON_TOP] = {{1,"salon_1","salon_1_dr",1,FALSE},
									   {2,"salon_2","salon_2_dr",1,FALSE},
									   {3,"salon_3","salon_3_dr",2,FALSE},
									   {4,"salon_4","salon_4_dr",2,FALSE},
									   {5,"salon_5","salon_5_dr",1,FALSE},
									   {6,"salon_6","salon_6_dr",1,FALSE},
									   {7,"salon_7","salon_7_dr",2,FALSE},
									   {8,"salon_8","salon_8_dr",2,FALSE}};

	//arc.id | arc.nacionalidasd | arc.tipo-sonido | arc.cant-jug | arc.cap-fichas | arc.salon-id |	arc.juego-id | arc.empty
	ArcadeEntity arList[ARCADE_TOP] = {{1,"nacion_1",1,2,100,1,1,FALSE},
										{2,"nacion_2",1,2,100,1,2,FALSE},
										{3,"nacion_3",2,4,100,2,3,FALSE},
										{4,"nacion_4",2,4,100,2,4,FALSE},
										{5,"nacion_5",1,2,100,3,5,FALSE},
										{6,"nacion_6",1,2,100,3,6,FALSE},
										{7,"nacion_7",2,4,200,4,1,FALSE},
										{8,"nacion_8",2,4,200,4,2,FALSE},
										{9,"nacion_9",1,2,100,5,3,FALSE},
										{10,"nacion_10",1,2,100,5,4,FALSE},
										{11,"nacion_11",2,4,100,6,5,FALSE},
										{12,"nacion_12",2,4,100,6,6,FALSE},
										{13,"nacion_13",1,5,100,7,1,FALSE},
										{14,"nacion_14",1,5,100,7,2,FALSE},
										{15,"nacion_15",2,1,200,8,3,FALSE},
										{16,"nacion_16",2,1,200,8,4,FALSE},
										{17,"nacion_17",2,1,200,8,4,FALSE}};*/

	SaloonEntity slList[SALON_TOP];
	ArcadeEntity arList[ARCADE_TOP];



	if(debug){
		sr_initSaloonListHardCd(slList,8,SALON_TOP);
		ar_initArcadeListHardCd(arList,18,ARCADE_TOP);
	}else{
		slId = 0;
		arId = 0;
		sr_initSaloonList(slList, SALON_TOP);
		ar_initArcadeList(arList, ARCADE_TOP);
		gr_initGameListHardCd(gmList, GAME_TOP,6, GAME_TOP);

	}

	char* menuOpts[STR_10] = {"1-Alta salon",
							  "2-Eliminar salon",
							  "3-Imprimir salones",
							  "4-Incorporar arcade",
							  "5-Modificar arcade",
							  "6-Eliminar arcade",
							  "7-Imprimir arcade",
							  "8-Imprimir juegos",
							  "9-Informes",
							  "0-SALIR"};

	int usrSlct; //opcion del menu que elige el usuario


	do{
		printf("-----      MENU        ------\n");
		str_showStringMatrix(menuOpts, 10);
		__fpurge(stdin);
		scanf("%d", &usrSlct);
		if(nmb_validateIntByRank(usrSlct,1,10)){
			_checkUsrSelection(gmList,arList,slList,usrSlct,&slId,&arId);
		}
	}while(usrSlct>=1 && usrSlct<=10);
}

//==========Private
void _checkUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int usrSlct,int *slId, int *arId){
	switch (usrSlct) {
		case 1:
			srv_createSaloon(slList, SALON_TOP, slId);
			break;
		case 2:
			srv_deleteSaloonById(slList, SALON_TOP, arList,ARCADE_TOP);
			break;
		case 3:
			srv_showAllSaloons(slList, SALON_TOP);
			break;
		case 4:
			srv_createArcade(arList, ARCADE_TOP, slList, SALON_TOP, gmList, GAME_TOP, arId);
			break;
		case 5:
			srv_updateArcade(arList, ARCADE_TOP, gmList, GAME_TOP);
			break;
		case 6:
			srv_deleteArcade(arList, ARCADE_TOP,slList, SALON_TOP, gmList, GAME_TOP);
			break;
		case 7:
			srv_showAllArcadesComplete(arList, ARCADE_TOP, slList, SALON_TOP, gmList, GAME_TOP);
			break;
		case 8:
			srv_showAllGamesInArcades(arList, ARCADE_TOP, gmList, GAME_TOP);
			break;
		case 9:
			_createShowReportsMenu(gmList,arList,slList);
			break;
		default:
			break;
	}
}

void _createShowReportsMenu(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList){
	int rpUsrSlc;

	char* reportMnOpts[STR_10] = {"\t 1-Salones mas 4 arcades [A]",
								  "\t 2-Arcades mas 2 jugadores [B]",
								  "\t 3-Listar info salon (por id) [C]",
								  "\t 4-Listar arcade-juego de un salon (por id) [D]",
								  "\t 5-Salon c/mas cant arcades [E]",
								  "\t 6-Salon recaudacion [F]",
								  "\t 7-Juego cantidad (en arcades) [G]",
								  "\t 0-Volver al menu principal"};
	do{
		printf("\t-----      Informes        ------\n");
		str_showStringMatrix(reportMnOpts,8);
		__fpurge(stdin);
		scanf("%d", &rpUsrSlc);
		if(nmb_validateIntByRank(rpUsrSlc,1,7)){
			_checkReportUsrSelection(gmList,arList,slList,rpUsrSlc);
		}
	}while(rpUsrSlc>=1 && rpUsrSlc<=7);
}

void _checkReportUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int rpUsrSlc){
	switch (rpUsrSlc) {
		case 1:
			printf("-***========================================***-\n");
			srv_showSaloonExceedArc(slList,SALON_TOP,arList,ARCADE_TOP,4);
			printf("-***========================================***-\n");
			break;
		case 2:
			printf("-***========================================***-\n");
			srv_showArcadeMorePlayerThan(slList,SALON_TOP,arList,ARCADE_TOP,2, gmList, GAME_TOP);
			printf("-***========================================***-\n");
			break;
		case 3:
			printf("-***========================================***-\n");
			srv_showSaloonInfo(slList, SALON_TOP, arList, ARCADE_TOP);
			printf("-***========================================***-\n");
			break;
		case 4:
			printf("-***========================================***-\n");
			srv_showArcadeAndGameInfoBySalonId(slList,SALON_TOP,arList,ARCADE_TOP,gmList,GAME_TOP);
			printf("-***========================================***-\n");
			break;
		case 5:
			printf("-***========================================***-\n");
			srv_showSaloonWithMaxArcade(slList,SALON_TOP,arList,ARCADE_TOP);
			printf("-***========================================***-\n");
			break;
		case 6:
			printf("-***========================================***-\n");
			srv_showSaloonIncome(slList,SALON_TOP,arList,ARCADE_TOP);
			printf("-***========================================***-\n");
			break;
		case 7:
			printf("-***========================================***-\n");
			srv_showAmountGameInArcades(arList,ARCADE_TOP, gmList, GAME_TOP);
			printf("-***========================================***-\n");
			break;
		default:
			break;
	}
}
