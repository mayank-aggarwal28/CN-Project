#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
	int sd,n,code,score,l;
	int test=1;
	char answers[100],sermsg[512];
	struct sockaddr_in addrs;
	sd=socket(AF_INET, SOCK_STREAM,0);
	addrs.sin_family=AF_INET;
	addrs.sin_addr.s_addr=inet_addr("127.0.0.1");	//172.16.59.26
	addrs.sin_port=htons(19900);		//19999
	
	int len=sizeof(addrs);
	int result=connect(sd,(struct sockaddr *)&addrs,len);
	if(result==-1)
	{
		perror("Connect client");
		exit(1);
	}

	recv(sd,sermsg,sizeof(sermsg),0);
	printf("\n%s",sermsg);

	while(1){
	
		send(sd,(int *)&test,sizeof(test),0);
		
		recv(sd,sermsg,sizeof(sermsg),0);		//THIS IS THE PROBLEM AGAIN!!
		printf("\n%s",sermsg);

		printf("\nAnswer: ");
		gets(answers);
	
		for(l=0;answers[l]!='\0';l++);
		//printf("\n%d\n",l);
		
		send(sd,answers,l,0);

		recv(sd,(int *)&code,sizeof(int),0);
	
		send(sd,(int *)&test,sizeof(test),0);
		
		if(code==1){				//Correct Answer
			recv(sd,sermsg,sizeof(sermsg),0);
			printf("\n%s",sermsg);

		}
		else{						//Wrong Answer
			recv(sd,sermsg,sizeof(sermsg),0);
			printf("\n%s",sermsg);
			
			send(sd,(int *)&test,sizeof(test),0);
			printf("abcd" );
			recv(sd,(int *)&score, sizeof(int),0);
			printf("\nScore: %d\n",score);
			
			break;
		}
	}
	
	//printf("Score; %d",score);
	printf("\nEnd of quiz!!\n");
	
	return 0;
}
