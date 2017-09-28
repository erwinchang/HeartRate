/*
*********************************************************************************************************
*               Copyright(c) 2017, ETEK Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      SimPress.C
* @brief      file of SimPress
* @details   
* @author    jiangs
* @date      2017-05-04
* @version   v0.1
* *********************************************************************************************************
*/



/* Includes ------------------------------------------------------------------*/
#include "system_config.h"
#include "SimPress.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* const define ------------------------------------------------------------------*/



const int timePara[]={
	0,			// 0
	-1,			// 1
	-5,			// 2
	-4,			// 3
	-2,			// 4
	0,			// 5
	1,			// 6
	3,			// 7
	6,			// 8
	4,			// 9
	2,			// 10
	1,			// 11
	1,			// 12
	1,			// 13
	0,			// 14
	0,			// 15
	3,			// 16
	5,			// 17
	4,			// 18
	0,			// 19
	0,			// 20
	-1,			// 21
	-1,			// 22
	-1,			// 23
	
	};

const uint8_t pressHigh[] = {
	90	,	//	50
	92	,	//	51
	93	,	//	52
	95	,	//	53
	96	,	//	54
	98	,	//	55
	99	,	//	56
	101	,	//	57
	102	,	//	58
	103	,	//	59
	105	,	//	60
	106	,	//	61
	108	,	//	62
	109	,	//	63
	111	,	//	64
	112	,	//	65
	114	,	//	66
	115	,	//	67
	117	,	//	68
	118	,	//	69
	120	,	//	70
	120	,	//	71
	120	,	//	72
	120	,	//	73
	120	,	//	74
	121	,	//	75
	121	,	//	76
	121	,	//	77
	121	,	//	78
	122	,	//	79
	122	,	//	80
	122	,	//	81
	122	,	//	82
	123	,	//	83
	123	,	//	84
	123	,	//	85
	123	,	//	86
	124	,	//	87
	124	,	//	88
	124	,	//	89
	124	,	//	90
	124	,	//	91
	125	,	//	92
	125	,	//	93
	125	,	//	94
	125	,	//	95
	125	,	//	96
	126	,	//	97
	126	,	//	98
	126	,	//	99
	126	,	//	100
	126	,	//	101
	127	,	//	102
	127	,	//	103
	127	,	//	104
	127	,	//	105
	128	,	//	106
	128	,	//	107
	128	,	//	108
	128	,	//	109
	129	,	//	110
	129	,	//	111
	129	,	//	112
	129	,	//	113
	130	,	//	114
	130	,	//	115
	130	,	//	116
	131	,	//	117
	131	,	//	118
	131	,	//	119
	132	,	//	120
	132	,	//	121
	132	,	//	122
	133	,	//	123
	133	,	//	124
	133	,	//	125
	134	,	//	126
	134	,	//	127
	134	,	//	128
	135	,	//	129
	135	,	//	130
	135	,	//	131
	136	,	//	132
	136	,	//	133
	136	,	//	134
	137	,	//	135
	137	,	//	136
	137	,	//	137
	137	,	//	138
	138	,	//	139
	138	,	//	140
	138	,	//	141
	138	,	//	142
	139	,	//	143
	139	,	//	144
	139	,	//	145
	139	,	//	146
	140	,	//	147
	140	,	//	148
	140	,	//	149
	140	,	//	150

};

const uint16_t pressLow[]={
	60	,	//	50
	62	,	//	51
	63	,	//	52
	64	,	//	53
	65	,	//	54
	66	,	//	55
	67	,	//	56
	68	,	//	57
	69	,	//	58
	70	,	//	59
	71	,	//	60
	72	,	//	61
	73	,	//	62
	74	,	//	63
	75	,	//	64
	76	,	//	65
	77	,	//	66
	78	,	//	67
	79	,	//	68
	80	,	//	69
	80	,	//	70
	80	,	//	71
	80	,	//	72
	80	,	//	73
	80	,	//	74
	81	,	//	75
	81	,	//	76
	81	,	//	77
	81	,	//	78
	81	,	//	79
	82	,	//	80
	82	,	//	81
	82	,	//	82
	82	,	//	83
	82	,	//	84
	83	,	//	85
	83	,	//	86
	83	,	//	87
	83	,	//	88
	83	,	//	89
	83	,	//	90
	83	,	//	91
	83	,	//	92
	84	,	//	93
	84	,	//	94
	84	,	//	95
	84	,	//	96
	84	,	//	97
	84	,	//	98
	84	,	//	99
	84	,	//	100
	84	,	//	101
	85	,	//	102
	85	,	//	103
	85	,	//	104
	85	,	//	105
	85	,	//	106
	85	,	//	107
	86	,	//	108
	86	,	//	109
	86	,	//	110
	86	,	//	111
	86	,	//	112
	86	,	//	113
	87	,	//	114
	87	,	//	115
	87	,	//	116
	87	,	//	117
	87	,	//	118
	87	,	//	119
	87	,	//	120
	87	,	//	121
	88	,	//	122
	88	,	//	123
	88	,	//	124
	88	,	//	125
	88	,	//	126
	88	,	//	127
	88	,	//	128
	88	,	//	129
	89	,	//	130
	89	,	//	131
	89	,	//	132
	89	,	//	133
	89	,	//	134
	89	,	//	135
	89	,	//	136
	89	,	//	137
	89	,	//	138
	90	,	//	139
	90	,	//	140
	90	,	//	141
	90	,	//	142
	90	,	//	143
	90	,	//	144
	90	,	//	145
	90	,	//	146
	90	,	//	147
	90	,	//	148
	90	,	//	149
	90	,	//	150

};
const uint16_t pressAge[]={
	95,	//	0
	95	,	//	1
	95	,	//	2
	95	,	//	3
	95	,	//	4
	95	,	//	5
	95	,	//	6
	95	,	//	7
	95	,	//	8
	95	,	//	9
	95	,	//	10
	95	,	//	11
	95	,	//	12
	95	,	//	13
	95	,	//	14
	95	,	//	15
	95	,	//	16
	95	,	//	17
	95	,	//	18
	95	,	//	19
	95	,	//	20
	95	,	//	21
	95	,	//	22
	95	,	//	23
	95	,	//	24
	95	,	//	25
	95	,	//	26
	95	,	//	27
	95	,	//	28
	95	,	//	29
	95	,	//	30
	97	,	//	31
	97	,	//	32
	97	,	//	33
	97	,	//	34
	97	,	//	35
	100	,	//	36
	100	,	//	37
	100	,	//	38
	100	,	//	39
	100	,	//	40
	103	,	//	41
	103	,	//	42
	103	,	//	43
	103	,	//	44
	103	,	//	45
	107	,	//	46
	107	,	//	47
	107	,	//	48
	107	,	//	49
	107	,	//	50
	111	,	//	51
	111	,	//	52
	111	,	//	53
	111	,	//	54
	111	,	//	55
	114	,	//	56
	114	,	//	57
	114	,	//	58
	114	,	//	59
	114	,	//	60

};










/* subroutine define ------------------------------------------------------------------*/


//#define RAND_MAX 100

uint16_t getBloodPress(uint16_t heartRate, int hour,int age,BLOOD_PRESS_T* bloodPress){
	double bloodPressHigh ,bloodPressLow;
	int x,agePara;
	uint8_t tempHigh,tempLow;
	 x = (int) (100.0 * rand() / (RAND_MAX + 1.0)) ;
	 x = x/20-2;
	 
	  APP_DBG(("x = %d\r\n",x));
	 if(heartRate<50){
	 		tempHigh= 90;
	 	}else if(heartRate>150){
	 		tempHigh= 150;
	 	}else {
	 		tempHigh=pressHigh[heartRate-50];
			 }
	  if(heartRate<50){
	 		tempLow= 60;
	 	}else if(heartRate>150){
	 		tempLow= 90;
	 	}else {
	 		tempLow=pressLow[heartRate-50];
	 			}	
		if(hour>23||hour<0){
			hour = 12;
			}
	 APP_DBG(("tempHigh = %d tempLow = %d\r\n",tempHigh,tempLow));	
	bloodPressHigh = tempHigh;
	bloodPressHigh = bloodPressHigh*(100+timePara[hour])/100;
	bloodPressHigh = bloodPressHigh*(100+x)/100;
	bloodPressLow = tempLow;
	bloodPressLow = bloodPressLow*(100+timePara[hour])/100;
	bloodPressLow = bloodPressLow*(100+x)/100;
	if(age>60){
		agePara = 116;
		}else {
		agePara = pressAge[age];
			}
	bloodPressHigh= bloodPressHigh*agePara/100;
	bloodPressLow= bloodPressLow*agePara/100;
	bloodPress->high =(uint16_t)bloodPressHigh;
	bloodPress->low=(uint16_t)bloodPressLow;
	return (uint16_t)x;
}
