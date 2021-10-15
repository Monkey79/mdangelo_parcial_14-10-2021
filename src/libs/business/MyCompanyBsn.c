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

void _checkUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int usrSlct,int slId, int arId);
void _createShowReportsMenu(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList);
void _checkReportUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int rpUsrSlc);

void bsn_startMyCompanyApp(void){
	int slId=8; //ultimo id creado
	int arId=16;
	int debug = TRUE;

	GameEntity gmList[GAME_TOP] = {{1,"game_1"},{2,"game_2"},{3,"game_3"},{4,"game_4"},{5,"game_5"},{6,"game_6"}};

	SaloonEntity slList[SALON_TOP] = {{1,"salon_1","salon_1_dr",1,FALSE},
									   {2,"salon_2","salon_2_dr",1,FALSE},
									   {3,"salon_3","salon_3_dr",2,FALSE},
									   {4,"salon_4","salon_4_dr",2,FALSE},
									   {5,"salon_5","salon_5_dr",1,FALSE},
									   {6,"salon_6","salon_6_dr",1,FALSE},
									   {7,"salon_7","salon_7_dr",2,FALSE},
									   {8,"salon_8","salon_8_dr",2,FALSE}};

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
										{16,"nacion_16",2,1,200,8,4,FALSE}};



	if(debug){
		sr_initSaloonListHardCd(slList,8,SALON_TOP);
		ar_initArcadeListHardCd(arList,16,ARCADE_TOP);
	}else{
		sr_initSaloonList(slList, SALON_TOP);
		ar_initArcadeList(arList, ARCADE_TOP);
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
			_checkUsrSelection(gmList,arList,slList,usrSlct,slId,arId);
		}
	}while(usrSlct>=1 && usrSlct<=10);
}

//==========Private
void _checkUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int usrSlct,int slId, int arId){
	switch (usrSlct) {
		case 1:
			printf("-alta salon-");
			break;
		case 2:
			printf("-eliminar salon-");
			break;
		case 3:
			printf("-imprimir salones-");
			break;
		case 4:
			printf("-crear arcade-");
			break;
		case 5:
			printf("-modificar arcade-");
			break;
		case 6:
			printf("-eliminar arcade-");
			break;
		case 7:
			printf("-imprimir arcades-");
			break;
		case 8:
			printf("-imprimir juegos-");
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

	char* reportMnOpts[STR_10] = {"\t1-Salones mas 4 arcades",
								  "\t2-Arcades mas 2 jugadores",
								  "\t3-Listar info salon (con argades y juegos)",
								  "\t4-Listar arcade de un salon",
								  "\t5-Salon c/mas cant arcades",
								  "\t6-Eliminar arcade",
								  "\t7-Salon recaudacion",
								  "\t0-Volver al menu principal"};
	do{
		printf("\t-----      Inormes        ------\n");
		str_showStringMatrix(reportMnOpts, 8);
		__fpurge(stdin);
		scanf("%d", &rpUsrSlc);
		if(nmb_validateIntByRank(rpUsrSlc,1,8)){
			_checkReportUsrSelection(gmList,arList,slList,rpUsrSlc);
		}
	}while(rpUsrSlc>=1 && rpUsrSlc<=7);
}

void _checkReportUsrSelection(GameEntity* gmList,ArcadeEntity* arList,SaloonEntity* slList,int rpUsrSlc){
	switch (rpUsrSlc) {
		case 1:
			printf("-1-Salones mas 4 arcades-\n");
			srv_showSaloonExceedArc(slList,SALON_TOP,arList,ARCADE_TOP,4);
			break;
		case 2:
			printf("-2-Arcades mas 2 jugadores-\n");
			break;
		case 3:
			printf("-3.Listar info salon (con argades y juegos)-\n");
			break;
		case 4:
			printf("-4-Listar arcade de un salon-\n");
			break;
		case 5:
			printf("-5-Salon c/mas cant arcades-\n");
			break;
		case 6:
			printf("-6-Eliminar arcade-\n");
			break;
		case 7:
			printf("-7-Salon recaudacion-\n");
			break;
		default:
			break;
	}
}
