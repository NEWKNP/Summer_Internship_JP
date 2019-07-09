/*  P2-2OS-EM.c  (Program 2-2)  */

/* --- �v���O�����̐��� ---
�@OS-EM�@�ōč\������v���O�����D

���́F
  1�D���e�f�[�^�̃t�@�C����
  2�D���e�f�[�^�̓��a�����̐��i���o��̐��j
  3�D���e�f�[�^�̊p�x�����̐��i���e���j
  4�D���e�f�[�^�̑S�p�x�i[2]�΂�[1]�΁j
  5�D�o�͂���摜�f�[�^�̃t�@�C����
  6�D�摜�f�[�^�̕��@�ix�����̉�f���j
  7�D�摜�f�[�^�̍����iy�����̉�f���j
  8�D�J��Ԃ��̐�
  9�D�T�u�Z�b�g�̐�

�o�́F
  �č\�������摜�f�[�^�̃t�@�C��
  ML-EM***.prj   : ����摜�̓��e
  ML-EM***hi.prj : �����e�Ƃ̔�
  ML-EM***bp.img : ��̋t���e�摜�i�Ō�̓��e�̂݁j
  ML-EM***.img   : �X�V���ꂽ�摜
  �� "***"�ɂ͌J��Ԃ��̉񐔂��}�������i��F001�j

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define  PI  3.14159265358979

// �O���[�o���ϐ��̐錾�Ə����l�ݒ�
char   g_f1[50] = "08RCP108AC.dat";    /* input file name */
int    g_px = 512;             /* number of bins (X) */
int    g_pa = 512;             /* number of projections (Thita) */
int    g_p2 = 2;               /* [2]pi or [1]pi */
char   g_f2[50] = "09OSEM108AC.dat"; /* output file name */
int    g_nx = 512;             /* number of matrix (x) */
int    g_ny = 512;             /* number of matrix (y) */
int    g_nit = 5;              /* number of iteration */
int    g_ss = 32;              /* number of subset */
float  *g_prj;                 /* projection data */
float  *g_img;                 /* reconstructed image data */
int    *g_cx;                  /* Detection probability (x value) */
float  *g_c0;                  /* Detection probability (x-1 detector) */
float  *g_c1;                  /* Detection probability (x+0 detector) */
float  *g_c2;                  /* Detection probability (x+1 detector) */

char *menu[] = { // ���͂̍ۂ̃R�����g�i���͕ϐ��ƃ����N�j
	"OS-EM reconstruction",
	"Projection file name <float>  ",
	"    Number of bins            ",
	"    Number of projections     ",
	"    [2]pi or [1]pi data       ",
	"Image file name <float>       ",
	"    Number of matrix  (x)     ",
	"    Number of matrix  (y)     ",
	"Number of iteration           ",
	"Number of subset              ",
};

void read_data(char *, float *, int);
void write_data(char *, float *, int);
void OSEM(float *, int, int, float *, int, int, int, int, int);

void getparameter()
{
	int   i;
	char  dat[256];

	// �ϐ��ւ̒l�̓���
	i = 0;
	fprintf( stdout, "\n%s\n\n", menu[i++] );
	fprintf( stdout, " %s [%s] :", menu[i++], g_f1 );
	if(*fgets(dat, 256, stdin) != '\n')  strncpy(g_f1, dat, strlen(dat)-1);
	fprintf( stdout, " %s [%d] :", menu[i++], g_px );
	if(*fgets(dat, 256, stdin) != '\n')  g_px = atoi(dat);
	fprintf( stdout, " %s [%d] :", menu[i++], g_pa );
	if(*fgets(dat, 256, stdin) != '\n')  g_pa = atoi(dat);
	fprintf( stdout, " %s [%d] :", menu[i++], g_p2 );
	if(*fgets(dat, 256, stdin) != '\n')  g_p2 = atoi(dat);
	fprintf( stdout, " %s [%s] :", menu[i++], g_f2 );
	if(*fgets(dat, 256, stdin) != '\n')  strncpy(g_f2, dat, strlen(dat)-1);
	fprintf( stdout, " %s [%d] :", menu[i++], g_nx );
	if(*fgets(dat, 256, stdin) != '\n')  g_nx = atoi(dat);
	fprintf( stdout, " %s [%d] :", menu[i++], g_ny );
	if(*fgets(dat, 256, stdin) != '\n')  g_ny = atoi(dat);
	fprintf( stdout, " %s [%d] :", menu[i++], g_nit );
	if(*fgets(dat, 256, stdin) != '\n')  g_nit = atoi(dat);
	fprintf( stdout, " %s [%d] :", menu[i++], g_ss );
	if(*fgets(dat, 256, stdin) != '\n')  g_ss = atoi(dat);
}

int main( void )
{
        clock_t start,end;
	// �v���O�����Ŏg�p����ϐ��̓���
	getparameter();

	// ���e�f�[�^�̈�̃������𓮓I�Ɋm��
	g_prj = (float *)malloc((unsigned long)g_px*g_pa*sizeof(float));
	g_img = (float *)malloc((unsigned long)g_nx*g_ny*sizeof(float));
	g_cx  = (int *)malloc((unsigned long)g_pa*g_nx*g_ny*sizeof(float));
	g_c0  = (float *)malloc((unsigned long)g_pa*g_nx*g_ny*sizeof(float));
	g_c1  = (float *)malloc((unsigned long)g_pa*g_nx*g_ny*sizeof(float));
	g_c2  = (float *)malloc((unsigned long)g_pa*g_nx*g_ny*sizeof(float));

	printf(" *** Read Projection data   ***\n");
	// ���e�f�[�^�̓���
	read_data(g_f1, g_prj, g_px*g_pa);

	printf(" *** OS-EM reconstruction ***\n");
	start = clock();
     	// OS-EM�@�̎��s
	OSEM(g_img, g_nx, g_ny, g_prj, g_px, g_pa, g_p2, g_nit, g_ss);
	end = clock();
	printf("reconstruction time : %f[s]\n",(float)(end-start)/CLOCKS_PER_SEC);

	printf(" *** Write Image data  ***\n");
	// �摜�f�[�^�̏o��
	write_data(g_f2, g_img, g_nx*g_ny);

	free(g_prj);
	free(g_img);

	return 0;
}

// �f�[�^�̈�̓��́ifloat�f�[�^�j
void read_data(char *fi, float *prj, int size)
{
	FILE   *fp;

	/* open file and read data */
	if(NULL == (fp = fopen(fi, "rb"))) {
		fprintf( stderr," Error : file open [%s].\n", fi);
		exit(1);
	}
	fread(prj, sizeof(float), size, fp);
	fclose(fp);
}

// �f�[�^�̈�̏o�́ifloat�f�[�^�j
void write_data(char *fi, float *prj, int size)
{
	FILE   *fp;

	/* open file and write data */
	if(NULL == (fp = fopen(fi, "wb"))) {
		fprintf( stderr," Error : file open [%s].\n", fi);
		exit(1);
	}
	fwrite(prj, sizeof(float), size, fp);
	fclose(fp);
}

void detection_probability(int px, int pa, int p2, int nx, int ny)
// ���o�m���̍s��i�W���s��j���쐬����֐�
// int    px;   ���e�̓��a�����̐�
// int    pa;   ���e�̊p�x�����̐�
// int    p2;   ���e�f�[�^�̑S�p�x�i[2]�΂�[1]�΁j
// int    nx;   �摜��x�����̐�
// int    ny;   �摜��y�����̐�
{
	int     i, j, k, ix;
	double  x, y, xx, th, a, b, x05, d, si, co;
	double  cc[3];

	for (i = 0; i < pa*nx*ny; i++)
	{
		g_cx[i] = 0;
		g_c0[i] = g_c1[i] = g_c2[i] = (float)0;
	}

	for (k = 0 ; k < pa ; k++)
	{
		th = p2 * PI * k / pa;
		si = sin(th);
		co = cos(th);
		if (fabs(si) > fabs(co))
		{
			a = fabs(si);
			b = fabs(co);
		}
		else
		{
			a = fabs(co);
			b = fabs(si);
		}
		for (i = 0; i < ny; i++)
		{
			y = ny / 2 - i;
			for (j = 0; j < nx; j++)
			{
				x = j - nx / 2;
				xx = x * co + y * si;

				cc[0] = cc[1] = cc[2] = 0.0;

				ix = (int)(floor(xx + 0.5));
				if (ix + px / 2 < 1 || ix + px / 2 > px - 2) continue;

				x05 = ix - 0.5;
				if ((d = x05 - (xx - (a - b) / 2)) > 0.0)
					cc[0] = b / (2 * a) + d / a;
				else if ((d = x05 - (xx - (a + b) / 2)) > 0.0)
					cc[0] = d * d / (2 * a * b);

				x05 = ix + 0.5;
				if ((d = xx + (a - b) / 2 - x05) > 0.0)
					cc[2] = b / (2 * a) + d / a;
				else if ((d = xx + (a + b) / 2 - x05) > 0.0)
					cc[2] = d * d / (2 * a * b);

				cc[1] = 1.0 - cc[0] - cc[2];

				g_cx[k*nx*ny+i*nx+j] = ix+px/2-1;
				g_c0[k*nx*ny+i*nx+j] = (float)cc[0];
				g_c1[k*nx*ny+i*nx+j] = (float)cc[1];
				g_c2[k*nx*ny+i*nx+j] = (float)cc[2];
			}
		}
	}
}

void projection_c_one(float *prj, int px, int pa, float *img, int nx, int ny, int k)
// ���o�m�����g���ē��e�f�[�^1���쐬����֐�
// float  *prj; �쐬����1�̊p�x�̓��e�f�[�^
// int    px;   ���e�̓��a�����̐�
// int    pa;   ���e�̊p�x�����̐�
// float  *img; ���ƂɂȂ�摜�f�[�^
// int    nx;   �摜��x�����̐�
// int    ny;   �摜��y�����̐�
// int    k;    �p�x�����̔ԍ�
{
	int    i;

	for(i = 0 ; i < px ; i++)
		prj[k*px+i] = 0;

	for(i = 0 ; i < nx*ny ; i++) 
	{
		prj[k*px+g_cx[k*nx*ny+i]+0] += (float)(g_c0[k*nx*ny+i]*img[i]);
		prj[k*px+g_cx[k*nx*ny+i]+1] += (float)(g_c1[k*nx*ny+i]*img[i]);
		prj[k*px+g_cx[k*nx*ny+i]+2] += (float)(g_c2[k*nx*ny+i]*img[i]);
	}

}

void backprojection_c_one(float *img, int nx, int ny, float *prj, int px, int pa, int k)
// ���o�m�����g���ē��e�f�[�^1����t���e����֐�
// float  *img; ���ƂɂȂ�摜�f�[�^
// int    nx;   �摜��x�����̐�
// int    ny;   �摜��y�����̐�
// float  *prj; �쐬����1�̊p�x�̓��e�f�[�^
// int    px;   ���e�̓��a�����̐�
// int    pa;   ���e�̊p�x�����̐�
// int    k;    �p�x�����̔ԍ�
{
	int    i;

	for(i = 0 ; i < nx*ny ; i++) 
	{
		img[i] += (float)(g_c0[k*nx*ny+i]*prj[k*px+g_cx[k*nx*ny+i]+0]);
		img[i] += (float)(g_c1[k*nx*ny+i]*prj[k*px+g_cx[k*nx*ny+i]+1]);
		img[i] += (float)(g_c2[k*nx*ny+i]*prj[k*px+g_cx[k*nx*ny+i]+2]);
	}

}

void OSEM(float *img, int nx, int ny, float *prj, int px, int pa, int p2, int nit, int ss)
// OS-EM�@�ōč\������֐�
// float  *img; �쐬����摜�f�[�^
// int    nx;   �摜��x�����̐�
// int    ny;   �摜��y�����̐�
// float  *prj; �ǂݏo�������e�f�[�^
// int    px;   ���e�̓��a�����̐�
// int    pa;   ���e�̊p�x�����̐�
// int    p2;   ���e�f�[�^�̑S�p�x�i[2]�΂�[1]�΁j
// int    nit;  �J��Ԃ��̉�
// int    ss;   �T�u�Z�b�g�̐�
{
	int     i, j, k, jj, m1, m2, *sub;
	char    fi[50];
	float   *aprj, *rprj, *aimg;

	aprj = (float *)malloc(px*pa*sizeof(float));
	rprj = (float *)malloc(px*pa*sizeof(float));
	aimg = (float *)malloc(nx*ny*sizeof(float));

	// �T�u�Z�b�g�̏��Ԃ����肷��
	sub = (int *)malloc(ss*sizeof(int));
	k = 0;
	for(i = 0 ; i < 32 ; i++)
		k += (ss >> i) & 1;
	if(k == 1) 
	{
		m1 = 0;
		sub[m1++] = 0;
		for(i = ss, m2 = 1 ; i > 1 ; i/=2, m2*=2) 
		{
			for(j = 0 ; j <  m2 ; j++)
				sub[m1++] = sub[j]+i/2;
		}
	}
	else 
	{
		for(i = 0 ; i < ss ; i++)
			sub[i] = i;
	}

	// ���o�m���̌v�Z
	detection_probability(px, pa, p2, nx, ny);

	// OS-EM itaration
	// �@ �����摜�����肷��
	for(i = 0 ; i < ny*nx ; i++)
		img[i] = 1;
	sprintf(fi, "OS-EM%03d.dat", 0);
	write_data(fi, img, nx*ny);  // �����摜�̏o��

	for(i = 0 ; i < nit ; i++) 
	{
		fprintf(stderr, "\r *** OS-EM iteration [%2d/%2d]", i+1, nit);
		for(k = 0 ; k < ss ; k++)  
		{
			// �A ����摜���瓊�e���v�Z����
			for(j = sub[k] ; j < pa ; j+=ss)
				projection_c_one(aprj, px, pa, img, nx, ny, j);

			// �B ���e�f�[�^�ƁC�A�Ōv�Z�������e�Ƃ̔���v�Z����
			for(j = sub[k] ; j < pa ; j+=ss)
			{
				for(jj = 0 ; jj < px ; jj++) 
				{
					// ����摜����̓��e�̒l���������Ƃ��͊���Z���s��Ȃ�
					if((double)aprj[j*px+jj] < 0.0001)
						rprj[j*px+jj] = prj[j*px+jj];
					else
						rprj[j*px+jj] = prj[j*px+jj]/aprj[j*px+jj];
				}
			}

			// �C �B�Ōv�Z���ꂽ����t���e����
			for(j = 0 ; j < nx*ny ; j++)
				aimg[j] = (float)0;
			for(j = sub[k] ; j < pa ; j+=ss)
				backprojection_c_one(aimg, nx, ny, rprj, px, pa, j);

			// �D �t���e�摜������摜�Ɋ|����i�摜�̍X�V�j
			for(j = 0 ; j < nx*ny ; j++)
				img[j] *= (float)aimg[j]*ss/pa;
		}
		sprintf(fi, "OSEM%03d.prj", i+1);
		//write_data(fi, aprj, px*pa);
		sprintf(fi, "OSEM%03dhi.prj", i+1);
		//write_data(fi, rprj, px*pa);
		sprintf(fi, "OSEM%03dbp.img", i+1);
		//write_data(fi, aimg, nx*ny);
		sprintf(fi, "OSEM%03d.dat", i+1);
		write_data(fi, img, nx*ny);
	}
	printf("\n");

	free(aprj);
	free(rprj);
	free(aimg);
}
