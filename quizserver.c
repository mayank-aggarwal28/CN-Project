#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>
#include<string.h>

int main()
{
	pid_t pid;
	int sd,nsd,clilen,n,index=0,code=0,l,i,flag=1,test;
	char questions[20][512], answers[20][100], buf[512];
	//char questions[512],answers[200],buf[512];
	char messages[3][300];
	FILE *fp1, *fp2, *fp3;
	struct sockaddr_in sadd,cadd;
	time_t t;
	
	fp1=fopen("Questions.txt","r");
	fp2=fopen("Answers.txt","r");
	
	for(i=0;i<5;i++){
		fgets(questions[i],512,fp1);
		
		//printf("\n%s\n",questions[i]);
		
		fgets(answers[i],512,fp2);
		
		//printf("\n%s\n",answers[i]);
	}
	
	fp3=fopen("Messages.txt","r");

	for(i=0;i<4;i++){
		fgets(messages[i],512,fp3);
		//printf("\n%s\n",messages[i]);
	}
	
	sd=socket(AF_INET, SOCK_STREAM,0);
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("127.0.0.1");			//inet_addr("172.16.59.7");
	sadd.sin_port=htons(19900);
	
	bind(sd,(struct sockaddr *)&sadd, sizeof(sadd));
	
	listen(sd,5);
	
	clilen=sizeof(cadd);
	
	//char hgi[]={'P','R','I','T','E','S','H','\0'};
	
	srand((unsigned) time(&t));
	
	for(;;)
	{
		nsd=accept(sd,(struct sockaddr *)&cadd,&clilen);
		
		
		if((pid=fork())==0)
		{
		
			int score=0;
			close(sd);
			n=send(nsd,messages[0],sizeof(messages[0]),0);
			
			while(index<20){
			
				
				//recv(nsd,(int*)&test,sizeof(test),0);
				
				//index=rand()%4;
			//printf("\n%d\n",index);
			//printf("\n%s\n",questions[index]);
				printf("\n%d\n",index);
				printf("\n%s\n",questions[index]);
				
				recv(nsd,(int*)&test,sizeof(test),0);
				
				n=send(nsd,questions[index],sizeof(questions[index]),0);		//THIS IS THE PROBLEM!!!!!!
			
			
				n=recv(nsd,buf,sizeof(buf),0);
				for(l=0;buf[l]!='\0';l++)
			
				printf("\n%c\n",buf[l]);
			
				for(i=0;i<l;i++){
			
					//printf("\n%s\n",answers[0]);
					
					if(buf[i]!=answers[index][i]){
						flag=0;
 					        n=send(nsd,(int *)&code,sizeof(int),0);
						recv(nsd,(int*)&test,sizeof(test),0);
						//n=send(nsd,messages[2],sizeof(messages[2]),0);
						//n=send(nsd,(int *)&score, sizeof(int),0);
						break;
					}
				}
				if(flag==0)
				{
					n=send(nsd,messages[2],sizeof(messages[2]),0);
					recv(nsd,(int*)&test,sizeof(test),0);
 					n=send(nsd,(int *)&score, sizeof(int),0);
                    break;
				}
				else {
					code=1;
				//printf("\nExecuted\n");
					n=send(nsd,(int *)&code,sizeof(int),0);
					recv(nsd,(int*)&test,sizeof(test),0);
					n=send(nsd,messages[1],sizeof(messages[1]),0);
					score+=10;
				}
				
				if(flag==0)
					break;

				index++;
			}
			
			close(nsd);

			exit(0);
		}
		close(nsd);
	}
 
	return 0;
}
