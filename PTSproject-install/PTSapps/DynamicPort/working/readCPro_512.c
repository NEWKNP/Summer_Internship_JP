#include <stdio.h>
#include <stdlib.h>
//#include <string.h>


int main(void)
{
    char filename1[50], filename2[50];
	int i, j;
	FILE *fp1, *fp2;
    float *prj;
    //float val;

    prj = (float *)malloc(512*512*sizeof(float));
    
    for(i=0; i<512*512; i++)
    {
        prj[i] = 0;
    }
    
    
    printf("Input file name : ");
    scanf("%s", filename1);
    
    if((fp1=fopen(filename1, "rb"))==NULL)
    {
        fprintf(stderr, "Error : file open [%s]. \n", filename1);
        exit(1);
    }
	for(i=0; i<512; i++)
	{
        for(j=0; j<512; j++)
        {
            fscanf(fp1, "%f", &prj[i*512+j]);
        }
    }

	fclose(fp1);

    
    printf("Output file name : ");
    scanf("%s", filename2);
    if((fp2 = fopen(filename2, "wb")) == NULL)
    {
        fprintf(stderr, "Error : file open [%s].\n", filename2);
        exit(1);
    }
    fwrite(prj, sizeof(float), 512*512, fp2);
    fclose(fp2);
    
    
    
    free(prj);
    
	return 0;

}
