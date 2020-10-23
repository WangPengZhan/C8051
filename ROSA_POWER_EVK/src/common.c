/*
 * FILE                : common.c
 * DESCRIPTION         : --
 * Author              : ysung
 * Copyright           : 2018-2019, xy-technology International Co.,Ltd
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 09/25/2019
 *
 * create.
 * --------------------
 */

//------------------------ Include files ------------------------//
#include    "include.h"

//--------------------- Function Prototype ----------------------//
void sort( uint16_t *buffer,int num );

//-------------------------- Variable ---------------------------//

//--------------------------- Function --------------------------//
/*
 * Name                : sort
 * Description         : ---
 * Author              : ysung
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 09/25/2019
 * 
 * create.
 * --------------------
 */
void sort(uint16_t *buffer,int num)
{
	int i,j;
	int temp;
	
	for(i = 0;i < (num - 1);++i){
		for(j = 0;j < (num - 1 - i);++j){
			if(buffer[j] < buffer[j + 1]){
				temp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = temp;
			}
		}
	}
	return;
}
