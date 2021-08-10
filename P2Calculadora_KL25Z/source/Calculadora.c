/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    Calculadora.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

	typedef struct{
		unsigned char bCurrentState;
		unsigned char bPreviousState;
	}tStateMachine;

	typedef struct{
		unsigned char bFirstData;
		unsigned char bSecondData;
		unsigned char bOperator;
		short wResult;
		short waDataBuffer[5];
		unsigned char bOperationCounter;
	}tCalcData;

	//void fnYourOwnName(tStateMachine * pSMStruct, tCalcData * pOperationData);

	void fnInitialState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnWaitFirstDataState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnWaitOperatorState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnWaitSecondDataState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnExecuteOperationState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnSaveResultState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnCalculateAverageState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	void fnResetState(tStateMachine *pSMStruct, tCalcData *pOperationData);
	unsigned char Transition;

int main(void) {
	tStateMachine pSMStruct;
	tCalcData pOperationData;

	void (*pArrayFn[])(tStateMachine*, tCalcData*) = {fnInitialState,  fnWaitFirstDataState, fnWaitOperatorState,
	fnWaitSecondDataState,  fnExecuteOperationState,  fnSaveResultState,  fnCalculateAverageState,  fnResetState};

	Transition = 0;

	while(1){

		(*pArrayFn[Transition])(&pSMStruct, &pOperationData);

	}
}
//---------------------------------------------------------------------------------
void fnInitialState(tStateMachine *pSMStruct, tCalcData *pOperationData) {
	pSMStruct->bCurrentState = 0;
	pSMStruct->bPreviousState = 0;
	pOperationData->bFirstData = 0;
	pOperationData->bSecondData = 0;
	pOperationData->bOperator = 0;
	pOperationData->wResult = 0;
	pOperationData->waDataBuffer[0] = 0;
	pOperationData->waDataBuffer[1] = 0;
	pOperationData->waDataBuffer[2] = 0;
	pOperationData->waDataBuffer[3] = 0;
	pOperationData->waDataBuffer[4] = 0;
	pOperationData->bOperationCounter = 0;
	Transition = 1;
}
//---------------------------------------------------------------------------------
void fnWaitFirstDataState(tStateMachine * pSMStruct, tCalcData * pOperationData){
	pSMStruct->bCurrentState = Transition;

	pSMStruct->bPreviousState = Transition;
	if(pOperationData->bFirstData >= 0xFF){
		Transition = 1; //Dato1 Invalido
	}else{
		Transition = 2; //Dato1 Valido
	}
}
//---------------------------------------------------------------------------------
void fnWaitOperatorState(tStateMachine * pSMStruct, tCalcData * pOperationData) {
	pSMStruct->bCurrentState = Transition;

	pSMStruct->bPreviousState = Transition;
	if(pOperationData->bOperator == '+'||pOperationData->bOperator == '-'||pOperationData->bOperator == '/'||pOperationData->bOperator == '*'||pOperationData->bOperator == '%'){
		 Transition = 3;
	}else{
			Transition = 7; //Operador invalido
	 }
}
//----------------------------------------------------------------------------------
void fnWaitSecondDataState(tStateMachine * pSMStruct, tCalcData * pOperationData) {
	pSMStruct->bCurrentState = Transition;

	pSMStruct->bPreviousState = Transition;
		if(pOperationData->bSecondData >= 0xFF){
			Transition = 3; //Dato2 Invalido
		}else{
			Transition = 4;
		}
}
//------------------------------------------------------------------------------
void fnExecuteOperationState(tStateMachine * pSMStruct, tCalcData * pOperationData){
	pSMStruct->bCurrentState = Transition;

	if(pOperationData->bOperator=='+'){
		pOperationData->wResult=pOperationData->bFirstData+pOperationData->bSecondData;
	}else if(pOperationData->bOperator=='-'){
		pOperationData->wResult=pOperationData->bFirstData-pOperationData->bSecondData;
	}else if(pOperationData->bOperator=='/'){
		pOperationData->wResult=pOperationData->bFirstData/pOperationData->bSecondData;
	}else if(pOperationData->bOperator=='*'){
		pOperationData->wResult=pOperationData->bFirstData*pOperationData->bSecondData;
	}else if(pOperationData->bOperator=='%'){
		pOperationData->wResult=pOperationData->bFirstData%pOperationData->bSecondData;
	}
	pOperationData->bOperationCounter++;

	pSMStruct->bPreviousState = Transition;
	Transition = 5;
}
//---------------------------------------------------------------------------------
void fnSaveResultState(tStateMachine * pSMStruct, tCalcData * pOperationData) {
	pSMStruct->bCurrentState = Transition;
	pOperationData->waDataBuffer[pOperationData->bOperationCounter - 1]=pOperationData->wResult;
	pSMStruct->bPreviousState = Transition;

	if(pOperationData->bOperationCounter == 5){

		Transition = 6;
	}else{

		Transition = 7;
	 }
}
//------------------------------------------------------------------------------
void fnCalculateAverageState(tStateMachine * pSMStruct, tCalcData * pOperationData) {
	pSMStruct->bCurrentState = Transition;
	unsigned char Sum = 0;
	for(unsigned char i = 0; i<=4 ; i++){
		Sum = Sum + pOperationData->waDataBuffer[i];
	}

	pOperationData->wResult = Sum / 5;
	pSMStruct->bPreviousState = Transition;

	Transition = 7;
}
//-------------------------------------------------------------------------------
void fnResetState(tStateMachine * pSMStruct, tCalcData * pOperationData) {
	pSMStruct->bCurrentState = Transition;

	pOperationData->bFirstData = 0xFF;
	pOperationData->bSecondData = 0xFF;
	pOperationData->bOperator = 0xFF;
	pOperationData->wResult = 0xFF;

	pSMStruct->bPreviousState = Transition;
	Transition = 1;
}
