#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

int main(void)
{
    int i;
    float *val;
    float *prj;
    FILE *fp1, *fp2;
    

    prj = (float *)malloc(512*512*sizeof(float));
    
    // input file name
    fp1 = fopen("./result/OSEM_XZ_16ss.dat", "rb");
	
    for(i=0; i<512*512; i++)
    {
      // printf("%d\n",i);
      // fread(val, sizeof(float), 1, fp1); //ayasii
      //  prj[i] = *val;
      fread(prj,sizeof(float),512*512,fp1);
    }

    fclose(fp1);
    	
    // output file name
    fp2 = fopen("./result/reconstruct_sinogram_xz_16ss.csv", "wb");
    
    for(i=0; i<512*512; i++)
    {
        fprintf(fp2, "%f\n", prj[i]);
    }
    
    fclose(fp2);
    
    free(prj);
 

	return 0;
}

