#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double sort_3(double gx,double gy,double gd);

int main(){
	FILE *fp;
	FILE *fp_a;
	FILE *fp_b;
	double a[500][15];
	double b[500][15];
	double dij[500][500];
	double gij[500][500];
	double word_distance[100];
	double min;
	int min_num;
	int total_num=0;
	int recog_rate = 0;
	char i,j;
	char m,n;
	int frame_a;
	int frame_b;
	char buff_a[256];
	char buff_b[256];
	double sum=0;
	double gx;
	double gy;
	double gd;
	char word_a[100][256];
	char word_b[100][256];
	char zero[] = "0";
	char clear[256]={'\0'};

	char filename_a[256]={'\0'};
	int num_a = 0;
	char str_a[256]={'\0'};
	char trans_a[256]={'\0'};

	char filename_b[256]={'\0'};
	int num = 0;
	char str[256]={'\0'};
	char trans[256]={'\0'};

	for(num_a=0;num_a<100;num_a++){
		
		/****** trans_filenum ******/
		if(num_a<9){
			strcpy(str_a,zero);
			strcat(str_a,zero);
		}
		else if(num_a<99){
			strcpy(str_a,zero);
		}
		snprintf(trans_a,256,"%d",num_a+1);
		strcat(str_a,trans_a);
		sprintf(filename_a,"city_mcepdata/city012/city012_%s.txt",str_a);
		strcpy(str_a,clear);   //initialize str
		strcpy(trans_a,clear); //initialize trans 

		for(num=0;num<100;num++){
		
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
			sprintf(filename_b,"city_mcepdata/city021/city021_%s.txt",str);
			strcpy(str,clear);   //initialize str
			strcpy(trans,clear); //initialize trans 

			/************* copy file ***************/
			if((fp=fopen(filename_a,"r"))==NULL){
				puts("ERROR");
				exit(1);
			}
			if((fp_a=fopen("cp_a.txt","w"))==NULL){
				puts("ERROR");
				exit(1);
			}
			for(i=0;fgets(buff_a,256,fp)!=NULL;i++){
				if(i>2)
	         	      		fprintf(fp_a,"%s",buff_a);
				else if(i==1)
					strcpy(word_a[num],buff_a);
			}
			fclose(fp);
			fclose(fp_a);
	
			if((fp=fopen(filename_b,"r"))==NULL){
				puts("ERROR");
				exit(1);
			}
			if((fp_b=fopen("cp_b.txt","w"))==NULL){
				puts("ERROR");
				exit(1);
			}	
			for(i=0;fgets(buff_b,256,fp)!=NULL;i++){
				if(i>2)
	         		       fprintf(fp_b,"%s",buff_b);
				else if(i==1)
					strcpy(word_b[num],buff_b);
			}
			fclose(fp);
			fclose(fp_b);


			/************ set array *************/
			if((fp_a=fopen("cp_a.txt","r"))==NULL){
				puts("ERROR");
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
				puts("ERROR");
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
			word_distance[num] = gij[frame_a-1][frame_b-1]/(frame_a + frame_b);
			if(num<1){
				min = word_distance[num];
				min_num = num;
			}
			else{
				if(word_distance[num]<min){
					min = word_distance[num];
					min_num = num;
				}
			}
		}

		if(num_a == min_num){
			recog_rate++;
		}
		printf("%d\nA: %sB: %sdistance: %f\n\n",num_a+1, word_a[num_a], word_b[min_num], min);
		
	}
	printf("recog_rate: %d\n",recog_rate);
	return 0;
}

/********************** function  ********************************/


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





