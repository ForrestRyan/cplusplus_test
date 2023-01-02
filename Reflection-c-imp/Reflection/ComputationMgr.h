
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
typedef struct InputParas {
	char* Name;
	double Value; 
	//void*   funP;
}InputParas_t;

typedef struct OutputParas {
	char* Name;
	double Value; 
	//void*   funP;
}OutputParas_t;

#endif

void StartComputation(char *ComputationConfig);