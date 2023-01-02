//#include "ComputationMgr.h"

#include "AlgorithmConfig.inc"
#include "string.h"

void Calculate(char *AlgorithmName)
{
	int ConfigSize = sizeof(ConfigMap)/sizeof(AlgorithmConfig_t);
	int index;
	for(index=0;index<ConfigSize;index++)
	{
		if(strcmpi(AlgorithmName,ConfigMap[index].Name)==0)
		{
			InputParas_t Paras[1]={"Depth",1};

			ConfigMap[index].Calculate(Paras);
		}
	}
		
	
}