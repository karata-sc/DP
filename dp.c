#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
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
	char buff[256];
	double sum=0;
	double gx=0;
	double gy=0;
	double gd=0;
	double sort[3];
	double pre;
	int ct=0;
	char word_a[100][256];
	char word_b[100][256];
	int wordnum=0;
	int cnt = 0;
	
	char filename_a[256]="city_mcepdata/city011/city011_001.txt";
	char filename_b[256]={'\0'};
	int num = 1;
	char clear[256]={'\0'};
	char snum[256]={'\0'};
	char num1[] = "0";
	char tnum[256]={'\0'};

	for(num=1;num<=100;num++){
		if(num<10){
			strcpy(snum,num1);
			strcat(snum,num1);
		}
		else if(num<100){
			strcpy(snum,num1);
		}
		snprintf(tnum,256,"%d",num);
		strcat(snum,tnum);


	//printf("%s\n",snum);
	sprintf(filename_b,"city_mcepdata/city012/city012_%s.txt",snum);
	strcpy(snum,clear);
	strcpy(tnum,clear);

	if((fp=fopen(filename_a,"r"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	if((fp1=fopen("cp_a.txt","w+"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	for(i=0;fgets(buff,256,fp)!=NULL;i++){
		if(i>2)
         	       fprintf(fp1,"%s",buff);
		else if(i==1)
			strcpy(word_a[num-1],buff);
	}

	if((fp=fopen(filename_b,"r"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	if((fp2=fopen("cp_b.txt","w+"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	for(i=0;fgets(buff,256,fp)!=NULL;i++){
		if(i>2)
         	       fprintf(fp2,"%s",buff);
		else if(i==1)
			strcpy(word_b[num-1],buff);
	}

	fclose(fp);
	fclose(fp1);
	fclose(fp2);

	/************** set array *******************/
	
	if((fp1=fopen("cp_a.txt","r"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	for(i=0,j=0;(fscanf(fp2,"%lf",&a[i][j]))!=EOF;){
		if(j>13){
			i++;
			j=0;
		}else j++;
	}
	frame_a = i;
	fclose(fp1);

	if((fp2=fopen("cp_b.txt","r"))==NULL){
	puts("<ERROR>");
	exit(1);
	}
	for(i=0,j=0;(fscanf(fp2,"%lf",&b[i][j]))!=EOF;){
		if(j>13){
			i++;
			j=0;
		}else j++;
	}
	frame_b = i;
	fclose(fp2);
	
	/***************** calc d(i,j)  *********************/
	
	for(i=0;i<frame_a;i++){
		for(m=0;m<frame_b;m++){
			for(n=0;n<15;n++){
				sum += pow((a[i][n]-b[m][n]),2);
			}
			dij[i][m] = sqrt(sum);
			sum = 0;
		}
	}
	/*for(i=0,j=0;i<frame_a;){
		if(j<frame_b){
			printf(" %f",dij[i][j]);
			j++;
		}else{
			printf("\n");
			j=0;
			i++;
		}
	}*/

	gij[0][0]=dij[0][0];

	for(i=1;i<frame_a;i++){
		gij[i][0]=dij[i][0]+gij[i-1][0];
	}

	for(j=1;j<frame_b;j++){
		gij[0][j]=dij[0][j]+gij[0][j-1];
	}

	for(i=1;i<frame_a;){
		for(j=1;j<frame_b;){
			gx=gij[i-1][j]+dij[i][j];
			gy=gij[i][j-1]+dij[i][j];
			gd=gij[i-1][j-1]+2*dij[i][j];
			
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
			gij[i][j]=sort[0];	

			j++;
		}
		i++;
		j=1;
	}

	/*for(i=0,j=0;i<frame_a;){
		if(j<frame_b){
			printf(" %f",gij[i][j]);
			j++;
		}else{
			printf("\n");
			j=0;
			i++;
		}
	}*/
	tgij+=gij[frame_a][frame_b];
	for(i=frame_a,j=frame_b;(i>0)&&(j>0);){
		sort[0]=gij[i][j-1];
		sort[1]=gij[i-1][j];
		sort[2]=gij[i-1][j-1];
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
		tgij+=sort[0];	

		if(sort[0]==gij[i][j-1])
			ct=0;
		if(sort[0]==gij[i-1][j])
			ct=1;
		if(sort[0]==gij[i-1][j-1]){
			ct=2;
		}
		else ;

		if(ct==0)
			i--;
		else if(ct==1)
			j--;
		else if(ct==2){
			i--;
			j--;
		}
	
	}
	if((i==0)&&(j==0));
	else if((i==0)&&(j>0)){
		for(;j>=0;j--){
			tgij+=gij[0][j];
		}
	}
	else if((i>0)&&(j==0)){
		for(;i>=0;i--){
			tgij+=gij[i][0];
		}
	}
	
	total[num-1] = tgij/(frame_a + frame_b);
	
	if(num == 1){
		total_min = total[num-1];	
		total_num = num;
	}
	else if(num > 1){
		if(total[num-1]<total_min){
			total_min = total[num-1];
			total_num = num;
		}
	}

	//printf("g(I,J) = %f\n",tgij);
	//printf("T = %f\n",total[num-1]);


	}

	printf("word_a: %sword_b: %sdistance: %f\n",word_a[0],word_b[total_num-1],total_min);
	

	return 0;
}
