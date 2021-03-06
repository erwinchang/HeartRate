/*
*********************************************************************************************************
*               Copyright(c) 2017, ETEK Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      lts1303m.C
* @brief      file of lts1303m
* @details   
* @author    jiangs
* @date      2017-05-04
* @version   v0.1
* *********************************************************************************************************
*/



/* Includes ------------------------------------------------------------------*/
#include "lts1303m.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nrf_gpio.h"
/* const define ------------------------------------------------------------------*/



#define RATE_NUM_MAX                        16
#define PLUSE_SAMPLE_MAX					16
#define WAVE_INDEX_MAX					16


const HEART_RATE_PULSE_T HeartRatePulseInit = 
{
	0,      /**< wave type . Like sine, squre sawtooth... */
    0,	    /**< peak index */
	0,	   /**< bottom index */
    0,		/*  上升沿时间   */
    0,     /*  下降沿时间  */
	0,	 /**<    起始点  > */
	0,	 /**<   结束点   > */		
	0,		 /**<  方向 0为上升 1 为下降    > */
	0,		 /**<  第几个波形    > */
};

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
/* ram define ------------------------------------------------------------------*/
uint16_t heartRate;   

uint16_t lastHeartRate;





uint16_t heartRateStack[RATE_NUM_MAX];
uint16_t heartRateTemp[RATE_NUM_MAX];
uint8_t  heartRateIndex ;




uint16_t pointValueCurrent;
uint16_t pointValueLast;

uint16_t pointCount;

uint16_t smooth;
uint16_t smoothValue;

SlopeDirection  direction;
uint8_t  upDirect,downDirect;
uint16_t topValue,bottomValue;
uint16_t topIndex,bottomIndex;
uint16_t topTempValue,bottomTempValue;
uint16_t topTempIndex,bottomTempIndex;
uint16_t upTrendCount,bottomTrendCount;


uint16_t topLength,bottomLength;

uint8_t	 pluseDirection = 0;
uint8_t  waveStart;

uint16_t period;
uint8_t firstPeriod;

SlopeDirection lastSlopeDirection;

HEART_RATE_PULSE_T pulseStacks[PLUSE_SAMPLE_MAX];
HEART_RATE_PULSE_T currentPulse;
uint8_t pulseIndex;



static HEART_RATE_PARAM_T HeartRateParam;

/**
  *
 **/





/* subroutine define ------------------------------------------------------------------*/


/**
  * @brief  This function getArrayMaxIndex
  * @param uint16_t  array[], int len
  * @retval array max index
  */
int getArrayMaxIndex(uint16_t *array,int len){
	int i,iMax;

    for(i=iMax=0;i<len;i++){
        if(array[iMax]<array[i]){
			  iMax=i;
        	}
          
    	}
    return iMax;
}

int getArrayMinIndex(uint16_t *array,int len){
	int i,iMin;

    for(i=iMin=0;i<len;i++)
        if(array[iMin]>array[i])
            iMin=i;
  
    return iMin;
}

uint16_t getArrayAverage(uint16_t *array,int length){
	int i = 0;
	int total = 0;
	for(i=0;i<length;i++){
		total +=array[i];
		}
	return total/length;
}


uint16_t getArrayAverageWithoutPeak(uint16_t *array,int length){
	int i = 0;
	int total = 0;
	int maxIndex,minIndex;
	uint16_t ave;
	minIndex = getArrayMinIndex(array,length);
	maxIndex = getArrayMaxIndex(array,length);
	
	for(i=0;i<length;i++){
		if(i!=maxIndex&&i!=minIndex){
			total +=array[i];
			}	
		}
	ave = total/(length-2);
	return ave;
}



void pushArrayData(uint16_t array[],int length,uint16_t data){
	
	int i = 0;

	for(i=length-1;i>0;i--){
		array[i] =array[i-1];
		}
	array[0] = data;
		
}


void clrArrayData(uint16_t array[],int length){
	
	int i = 0;

	for(i=0;i<length;i++){
		array[i] =0;
		}
	
		
}

uint16_t getSlope(uint16_t max,uint16_t min,uint16_t time){
	
	uint16_t slope = 0;
	slope = (max-min)/time;
	return slope;
		
}


uint16_t getSlopeValue(uint16_t before,uint16_t after){
	uint16_t slope = 0;
	if(before>after){
		slope = before-after;
		}else {
			slope = after-before;
			}
	return slope;
		
}

/**
  * @brief  比较前后两值大小，当前面大于后面 返回0 否则返回1
  * @param uint16_t before,uint16_t after
  * @retval type
  */
uint8_t getSlopeType(uint16_t before,uint16_t after){
	
	if(before>after){
		return 0;
		}else {
		return 1;
		}	
}


/**
  * @brief  比较前后两值大小，当前面大于后面 返回0 否则返回1
  * @param uint16_t before,uint16_t after
  * @retval SLOPE_T
  */
SLOPE_T getSlopeObj(uint16_t before,uint16_t after){

	SLOPE_T slopeObj;
	
	if(before>after){
		
		slopeObj.value= before-after;
		slopeObj.direction =SlopeUp;
		}else {

		slopeObj.value= after-before;
		slopeObj.direction = SlopeDown;	
		}
		
	if(slopeObj.value<HeartRateParam.waveSlopeRange){
		slopeObj.smooth =1;
		}else {
		slopeObj.smooth =0;
		}
		
	return slopeObj;
}



void pushPulseStack(){
	currentPulse.index=pulseIndex;
	memcpy(&pulseStacks[pulseIndex],&currentPulse,sizeof(currentPulse));
	pulseIndex++;
	
}
void  clrPulseStack(){
	int i = 0;
	for(;i<PLUSE_SAMPLE_MAX;i++)
	memcpy(&pulseStacks[i],&HeartRatePulseInit,sizeof(currentPulse));

}

void clrCurrentPulse(){

	memcpy(&currentPulse,&HeartRatePulseInit,sizeof(currentPulse));

}



void heartRateInit(void){
	printf(" heartRateInit \r\n" );
	pointCount = 0;
	heartRateClrRam();
}
void printCurrentPluse(){
	printf(" cp[%d] t=%d s=%d e=%d p=%d u=%d d=%d tl=%d bl=%d ti=%d\r\n",currentPulse.index,currentPulse.type,currentPulse.startPointIndex,currentPulse.endPointIndex,currentPulse.period,
		currentPulse.upTime,currentPulse.downTime,currentPulse.topLength,currentPulse.bottomLength,currentPulse.topIndex);
}

void heartRateClrRam(void){
	
	pointValueLast = 0;	
	smooth = 0;
	pluseDirection = 0;
	waveStart = 0;
	pulseIndex = 0;
	upDirect =0;
	downDirect = 0;
	bottomLength = 0;
	topLength = 0;
	firstPeriod = 0;
	
}


void clrHeartRateStack(){

	lastHeartRate = 0;
	heartRateIndex = 0;

	clrArrayData(heartRateStack,RATE_NUM_MAX);
	
}


void heartRateParamSetup(HEART_RATE_PARAM_T _heartRateParam){

	memcpy(&HeartRateParam,&_heartRateParam,sizeof(_heartRateParam));
	HeartRateParam.oneMinutePoint = 60000/HeartRateParam.sampleRate;
	HeartRateParam.periodMax = HeartRateParam.oneMinutePoint/HeartRateParam.heartRateMIN;
	HeartRateParam.periodMin = HeartRateParam.oneMinutePoint/HeartRateParam.heartRateMAX;
}


uint16_t getHeartRateFilter(){
	//lastHeartRate 
	
	// heartRate = SamplePointFull/(waveUp+waveDown);
	int i = 0;
	int peaks[WAVE_INDEX_MAX];
	uint16_t hearts[WAVE_INDEX_MAX];
	SLOPE_T slopeObj;
	int count =0;
	
	
	for(;i<pulseIndex;i++){
		currentPulse = pulseStacks[i];
	//	printCurrentPluse();
		if(pulseStacks[i].type==1){
			if((pulseStacks[i].topIndex-(pulseStacks[i].topLength/2))>0){
				
				peaks[i] = pulseStacks[i].topIndex-(pulseStacks[i].topLength/2);
			}else {
				peaks[i] = pulseStacks[i].topIndex;
			}
		
		}else {
				peaks[i] = pulseStacks[i].topIndex;
		}
		// printf(" peaks[%d]= %d\r\n",i,peaks[i] );
	}
	
	for(i=0;i<(pulseIndex-1);i++){
		heartRate = HeartRateParam.oneMinutePoint/ (peaks[i+1]-peaks[i]);
		if(heartRate<=HeartRateParam.heartRateMAX&&heartRate>=HeartRateParam.heartRateMIN){
			hearts[count++]=heartRate;
		
			}
		//	 printf(" heart [%d]= %d\r\n",i,heartRate );
		
		
	}
	if(count!=0){
	heartRate =	getArrayAverage(hearts,count);
	 printf(" heart first = %d\r\n",heartRate );
	}else {
	heartRate = lastHeartRate;
		}
	
	//for(;i<pulseIndex;i++){
	//	pushArrayData(heartRateTemp,pulseIndex,pulseStacks[i].heartRate);
	//	}
//	heartRate = getArrayAverage(heartRateTemp,pulseIndex);
	
	if(heartRate>HeartRateParam.heartRateMAX){
		
		if(lastHeartRate>0){
			heartRate = lastHeartRate;
			return heartRate;
			}else {
			heartRate= HeartRateParam.heartRateMAX;
			lastHeartRate = heartRate;
			return heartRate;
			}
		}
	
	if(heartRate<HeartRateParam.heartRateMIN){
		if(lastHeartRate>0){
			heartRate = lastHeartRate;
			return heartRate;
			}else {
			heartRate= HeartRateParam.heartRateMIN;
			lastHeartRate = heartRate;
			return heartRate;
				}
		}
	if(lastHeartRate!=0){
		
		slopeObj = getSlopeObj(heartRate,lastHeartRate);
		if(slopeObj.smooth<10){
				
			heartRate = (heartRate+lastHeartRate)/2;
			
			 printf(" little change heart = %d\r\n",heartRate );
		}else {
			if(slopeObj.direction>0){
				heartRate = lastHeartRate-1;
				heartRateIndex = 0;
				
			}else {
				heartRate = lastHeartRate+1;
			}
			heartRateStack[heartRateIndex]=heartRate;
			heartRateIndex++;
			if(heartRateIndex>8){
				heartRate = getArrayAverageWithoutPeak(heartRateStack,8);
				}
			
		
			
		}
	}
	lastHeartRate = heartRate;	
		return heartRate;
	
}



HRState getHeartRateWaves(uint16_t adData)   {   
 	
	HRState state;
	SLOPE_T slopeObj;

	
	
	
	state = HRInit;
	
	pointValueCurrent  = adData;
	
	slopeObj = getSlopeObj(pointValueCurrent,pointValueLast);
	
	if(slopeObj.smooth!=0) {				// 数据波动较小
		smooth++;
		smoothValue = pointValueCurrent;
		if(lastSlopeDirection==SlopeDown){
			
			downDirect++;
			bottomLength++;
			}else {
			upDirect++;
			topLength++;
			}
		if(smooth>HeartRateParam.recDetectData){
			currentPulse.type= 1;
			
			}
		if(smooth>HeartRateParam.evennessMax){
				state = HRLineOut;
				if(smoothValue<50){
				direction = SlopeDown;
				}else if(smoothValue>1000){
				 	direction = SlopeUp;
				}
			}
		}else {
		
		
		lastSlopeDirection = slopeObj.direction;
		smooth=0;
		
		}
	
	
	if(lastSlopeDirection==SlopeDown){					//当前点的斜率方向向下
	
		nrf_gpio_pin_clear(27);

		if(direction==SlopeUp){						//前面向上 --|__
	
			direction = SlopeDown;
			downDirect = 0;
			topTempIndex = pointCount;
			topTempValue = pointValueCurrent;
			}							
			downDirect++;	
			
		
		
	
		
		
		}else {	
		
		nrf_gpio_pin_set(27);
			
		if(direction==SlopeDown){			//前面向下		 __|--
			
		
			bottomTempIndex = pointCount;
			period = upDirect+downDirect;
		//	printf(" p[%d] u=%d d=%d p=%d\r\n",pointCount,upDirect,downDirect,period);
		if(period<HeartRateParam.evennessMax&&period>HeartRateParam.periodMin){
				
				if(firstPeriod==0){
					currentPulse.startPointIndex=pointCount;
					firstPeriod = 1;
					}else {
					currentPulse.endPointIndex=pointCount;
					currentPulse.upTime = upDirect;
				    currentPulse.downTime = downDirect;
					currentPulse.bottomLength =bottomLength;
					currentPulse.topLength=topLength;
					currentPulse.topIndex = topTempIndex;
					currentPulse.period = period;
					pushPulseStack();
					printCurrentPluse();
					clrCurrentPulse();
					currentPulse.startPointIndex=pointCount;
					if(pulseIndex>HeartRateParam.waveArrayMax){
					//	clrPulseStack();
						state = HRFinish;
						}
					}
				upDirect = 0;
				downDirect = 0;
				bottomLength = 0;
				topLength = 0;
					
				
				}
				else if(upDirect<10) {

				}
			upDirect = 0;
			direction = SlopeUp;
		}
		upDirect++;		
			
		
		
		
		
		
		
		}
	
	
	pointValueLast = pointValueCurrent;
	pointCount++;
	if(pointCount>=HeartRateParam.samplePointMax){
		state = HRPointMax;
		}
	return state;
	
} 


//#define RAND_MAX 100

uint16_t getBloodPress(uint16_t heartRate, int hour,int age,BLOOD_PRESS_T* bloodPress){
	double bloodPressHigh ,bloodPressLow;
	int x,agePara;
	uint8_t tempHigh,tempLow;
	 x = (int) (100.0 * rand() / (RAND_MAX + 1.0)) ;
	 x = x/20-2;
	 
	  printf("x = %d\r\n",x);
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
	 printf("tempHigh = %d tempLow = %d\r\n",tempHigh,tempLow);	
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

