#include "vis.h"

void visualize(){
        printf("\n-----------------------------------\n");
        printf(" Employees with Highest Work Hours :\n");
        printf("-----------------------------------\n\n");
        int j;
        for(j = 0; j < NUMNODES; j++){
                // Well.. I think that's the definition of a top work hour :)
                if(top_work_hours[j] >= 1400){
                       printf("%s %s : %d\n", company[j%26],position[j % 39], top_work_hours[j]);
		}

        }
}

