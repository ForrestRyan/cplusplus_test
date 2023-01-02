#include<stdio.h>
#include "DecisionTreeAlgorithm.inc"
#include "BayesAlgorithm.inc"
#include "ComputationMgr.h"

//#ifndef __FUNCTION_H__
//#define __FUNCTION_H__

//extern int DecisionTreeCalculate(InputParas_t *InputParas);
//extern int BayesCalculate(InputParas_t *InputParas);

typedef struct AlgorithmConfig {
	char* Name;
	int (*Calculate)(InputParas_t *InputParas); 
	//void*   funP;
}AlgorithmConfig_t;

//#endif

AlgorithmConfig_t ConfigMap[2]={
		{"DecisionTree",DecisionTreeCalculate},
		{"Bayes",BayesCalculate}
		//{"KMeans",KMeansCalculate}
	};

