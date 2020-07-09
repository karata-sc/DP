#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void print_dp(int n,char a[64],char b[64],double total);
double sort_3(double gx,double gy,double gd);

int main(){
	FILE *fp;
	FILE *fp_a;
	FILE *fp_b;
	double a[500][15];
	double b[500][15];
	double dij[500][500];
	double gij[500][500];
	double tgij=0;
	double total[100];
	double total_min=0;
	int total_num=0;
	char data[50][50][256]={'\0'};
	char i,j;
	char m,n;
	int frame_a;
	int frame_b;
	char buff_a[256];
	char buff_b[256];
	double sum=0;
	double gx=0;
	double gy=0;
	double gd=0;
	double pre;
	double set = 0;
	int ct=0;
	char word_a[100][256];
	char word_b[100][256];
	int wordnum=0;
	int cnt = 0;
	char t[64];
	double sumf = 0;
	double sumf2 = 0;	

	char filename_a[256]="city_mcepdata/city011/city011_099.txt";
	char filename_b[256]={'\0'};

	int num = 0;

	char zero[] = "0";
	char str[256]={'\0'};
	char trans[256]={'\0'};
	char clear[256]={'\0'};

	for(num=0;num<100;num++){
		
		tgij = 0; //initialize tgij

		/****** trans_filenum ******/
		if(num<9){
			strcpy(str,zero);
			strcat(str,zero);
		}
		else if(num<99){
			strcpy(str,zero);
		}
		snprintf(trans,256,"%d",num+1);
		strcat(str,trans);
		sprintf(filename_b,"city_mcepdata/city012/city012_%s.txt",str);
		strcpy(str,clear);   //initialize str
		strcpy(trans,clear); //initialize trans 


		/************* copy file ***************/
		if((fp=fopen(filename_a,"r"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		if((fp_a=fopen("cp_a.txt","w"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		for(i=0;fgets(buff_a,256,fp)!=NULL;i++){
			if(i>2)
         	      	 fprintf(fp_a,"%s",buff_a);
			else if(i==1)
				strcpy(word_a[num],buff_a);
		}
	
		if((fp=fopen(filename_b,"r"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		if((fp_b=fopen("cp_b.txt","w"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		for(i=0;fgets(buff_b,256,fp)!=NULL;i++){
			if(i>2)
	         	       fprintf(fp_b,"%s",buff_b);
			else if(i==1)
				strcpy(word_b[num],buff_b);
		}

		fclose(fp);
		fclose(fp_a);
		fclose(fp_b);


		/************ set array *************/
		if((fp_a=fopen("cp_a.txt","r"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		for(i=0,j=0;(fscanf(fp_a,"%lf",&a[i][j]))!=EOF;){
			if(j>13){
				i++;
				j=0;
			}else j++;
		}
		frame_a = i;
		fclose(fp_a);

		if((fp_b=fopen("cp_b.txt","r"))==NULL){
			puts("<ERROR>");
			exit(1);
		}
		for(i=0,j=0;(fscanf(fp_b,"%lf",&b[i][j]))!=EOF;){
			if(j>13){
				i++;
				j=0;
			}else j++;
		}
		frame_b = i;
		fclose(fp_b);
	

		/*********** calc d(i,j) ************/
		for(i=0;i<frame_a;i++){
			for(m=0;m<frame_b;m++){
				for(n=0;n<15;n++){
					sum += pow((a[i][n]-b[m][n]),2);
				}
				dij[i][m] = sqrt(sum);
				sum = 0;
			}
		}

		
		/*********** calc g(i,j) ***********/
		gij[0][0]=dij[0][0];

		for(i=1;i<frame_a;i++){
			gij[i][0]=dij[i][0]+gij[i-1][0];
		}

		for(j=1;j<frame_b;j++){
			gij[0][j]=dij[0][j]+gij[0][j-1];
		}

		for(i=1;i<frame_a;i++){
			for(j=1;j<frame_b;j++){
				gx=gij[i-1][j]+dij[i][j];
				gy=gij[i][j-1]+dij[i][j];
				gd=gij[i-1][j-1]+2*dij[i][j];
				gij[i][j] = sort_3(gx,gy,gd);	
			}
		}
		sumf = (double)(frame_a + frame_b);
		total[num] = gij[frame_a-1][frame_b-1]/sumf;
		//sumf2 = gij[frame_a-1][frame_b-1];
		//printf("%d  |  %f\n",num+1,sumf2);
		//printf("%d  |  A %d |B  %d\n",num+1,frame_a,frame_b);
		print_dp(num+1,word_a[0],word_b[num],total[num]);
		//print_dp(num+1,word_a[0],word_b[num],gij[frame_a - 1][frame_b - 1]);
	}
	/*for(i=0;i<frame_b;i++){
		for(j=0;j<15;j++){
			printf("%f ",b[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}

/********************** function  ********************************/

void print_dp(int n,char a[64],char b[64],double total){
	char w[64];
	strncpy(w,a,3);
	w[3]='\0';
	printf("%d %s ",n,w);
	strncpy(w,b,3);
	w[3]='\0';
	printf("%s %f\n",w,total);
}

double sort_3(double gx,double gy,double gd){
	double sort[3];
	double pre=0;
	sort[0]=gx;
	sort[1]=gy;
	sort[2]=gd;
	if(sort[1]>sort[2]){
		pre=sort[1];
		sort[1]=sort[2];
		sort[2]=pre;	
	}
	if(sort[0]>sort[1]){
		pre=sort[0];
		sort[0]=sort[1];
		sort[1]=pre;
	}
	return sort[0];
}





