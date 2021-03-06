


#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int main()	{

	float u[6], a[3];
	FILE *Proximal,*Distal;
	Proximal=fopen("Proximal_indus.txt","w"); // Stores input angles to industrial robot forward kinematics
	Distal=fopen("Distal_indus.txt","w"); // Stores output 3 dimensions from industrial robot forward kinematics

	float mat[][4]={1.0000,   -0.0068,   -0.0099, -724.6238,
    				0.0068,    0.9999,   -0.0020,  679.1527,
    				0.0099,    0.0019,    1.0000, -315.8471,
         			0,         0,         0,    1.0000};
	float c[4];

	for (u[0] = -0.17; u[0] > -1.4; u[0]-=0.0305){	
		for (u[1] = 1.57; u[1] > -0.35; u[1]-=0.0451){
			for (u[2] = 2.44; u[2] > 0.17; u[2]-=0.05){
				for (u[3] = 4.71; u[3] > -4.71; u[3]-=0.44){
					for (u[4] = 2.27; u[4] > -2.01; u[4]-=0.227){
						//for (u[5] = 4.71; u[5] > -4.71; u[5]-=0.94){
							u[5]=0;
							a[0]= 49.657*cos(u[0]) - 50.337*sin(u[0]) + 550.0*sin(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) + 500.0*sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 500.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876) + 0.00080811*sin(u[3])*(cos(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 1.0*sin(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876))) - 0.00080811*cos(u[3])*(3.6732e-6*sin(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 0.99996*sin(u[0]) - 0.0068195*cos(u[0]) + 3.6732e-6*cos(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) + 3.6319e-8) + 320.0*sin(u[4])*(cos(u[3])*(cos(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 1.0*sin(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876))) + sin(u[3])*(3.6732e-6*sin(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 0.99996*sin(u[0]) - 0.0068195*cos(u[0]) + 3.6732e-6*cos(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) + 3.6319e-8)) + 320.0*cos(u[4])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 1.0*sin(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 3.6732e-6*sin(u[3])*(cos(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 1.0*sin(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876))) + 3.6732e-6*cos(u[3])*(3.6732e-6*sin(u[2])*(cos(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) + sin(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 0.99996*sin(u[0]) - 0.0068195*cos(u[0]) + 3.6732e-6*cos(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) + 3.6319e-8) + 1.0*cos(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 1.3341e-13) + 550.0*cos(u[2])*(sin(u[1])*(0.99996*cos(u[0]) - 0.0068195*sin(u[0])) - 1.0*cos(u[1])*(2.5049e-8*cos(u[0]) + 3.673e-6*sin(u[0]) + 0.0098876)) - 729.35;

        					a[1]=50.335*cos(u[0]) + 49.658*sin(u[0]) + 550.0*sin(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 500.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + 550.0*cos(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) - 500.0*cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672) - 320.0*sin(u[4])*(cos(u[3])*(sin(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) - cos(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672))) - sin(u[3])*(0.99995*cos(u[0]) - 0.0067809*sin(u[0]) + 3.6732e-6*sin(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 3.6732e-6*cos(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 7.226e-9)) + 320.0*cos(u[4])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 1.0*sin(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 1.0*cos(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 3.6732e-6*cos(u[3])*(0.99995*cos(u[0]) - 0.0067809*sin(u[0]) + 3.6732e-6*sin(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 3.6732e-6*cos(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 7.226e-9) + 3.6732e-6*sin(u[3])*(sin(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) - cos(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672))) - 2.6543e-14) - 0.00080811*cos(u[3])*(0.99995*cos(u[0]) - 0.0067809*sin(u[0]) + 3.6732e-6*sin(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 3.6732e-6*cos(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) + 7.226e-9) - 0.00080811*sin(u[3])*(sin(u[2])*(1.0*sin(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) - cos(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672)) - cos(u[2])*(cos(u[1])*(0.0067809*cos(u[0]) + 0.99995*sin(u[0])) + sin(u[1])*(2.4907e-8*sin(u[0]) - 3.673e-6*cos(u[0]) + 0.0019672))) + 678.21;


        					a[2]= 0.59233*cos(u[0]) - 0.39906*sin(u[0]) - 0.00080811*sin(u[3])*(cos(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + sin(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0])))) - 550.0*sin(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + 550.0*cos(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) - 320.0*sin(u[4])*(cos(u[3])*(cos(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + sin(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0])))) + sin(u[3])*(0.0099141*sin(u[0]) - 0.0019326*cos(u[0]) + 3.6732e-6*sin(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) - 3.6732e-6*cos(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + 3.6732e-6)) + 500.0*cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + 320.0*cos(u[4])*(3.6417e-8*sin(u[0]) - 7.0988e-9*cos(u[0]) + 3.6732e-6*sin(u[3])*(cos(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + sin(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0])))) - 1.0*sin(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + 1.0*cos(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) - 3.6732e-6*cos(u[3])*(0.0099141*sin(u[0]) - 0.0019326*cos(u[0]) + 3.6732e-6*sin(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) - 3.6732e-6*cos(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + 3.6732e-6) + 1.3492e-11) + 0.00080811*cos(u[3])*(0.0099141*sin(u[0]) - 0.0019326*cos(u[0]) + 3.6732e-6*sin(u[2])*(sin(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) - 1.0*cos(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) - 3.6732e-6*cos(u[2])*(cos(u[1])*(7.0988e-9*cos(u[0]) - 3.6417e-8*sin(u[0]) + 1.0) + sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0]))) + 3.6732e-6) + 500.0*sin(u[1])*(0.0099141*cos(u[0]) + 0.0019326*sin(u[0])) + 162.15;
//a[3]=1;
	
//a[0]=1454.05;
//a[1]=-1367.64;
//a[2]=873.36;
//a[3]=1;
/*	int i,j,k;
	float sum;
	for(i=0;i<4;i++)  
           c[i]=0;

      for(i=0;i<4;i++){ //row of first matrix
      //column of second matrix
           sum=0;
           for(k=0;k<4;k++){
               sum=sum+mat[i][k]*a[k];
			}
           c[i]=sum;
      
      
	}
	a[0] = c[0];
	a[1] = c[1];
	a[2] = c[2];
	a[3] = c[3];
	printf("%f\t  %f\t  %f\n",a[0],a[1],a[2]);

*/


							if (a[0] > -50 && a[0] <270 && a[1] > -50 && a[1] < 260 && a[2] >0 && a[2] <200) {
								fprintf(Proximal,"%f\t  %f\t  %f\t  %f\t  %f\t  %f\n",u[0],u[1],u[2],u[3],u[4],u[5]);
								fprintf(Distal, "%f\t  %f\t  %f\n",a[0],a[1],a[2]);
							}
						//}
					}	
				}	
			}		
		}		
	}
	fclose(Proximal);
	fclose(Distal);



}
