#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char const *argv[])
{
    time_t clock;
    char dataSending[1025];                                              //pakiet zawierajacy dane i wysylajcy je
    int clintListen = 0;
    int clintConnect = 0;
    struct sockaddr_in ipOfServer;
    clintListen = socket(AF_INET, SOCK_STREAM, 0);                      //tworzenie gniazda
    memset(&ipOfServer, '0', sizeof(ipOfServer));
    memset(dataSending, '0', sizeof(dataSending));
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_addr.s_addr = htonl(INADDR_ANY);
    ipOfServer.sin_port = htons(2017);                                  //numer portu servera
    bind(clintListen, (struct sockaddr*) &ipOfServer, sizeof(ipOfServer));
    listen(clintListen, 20);
    
    
    while(1){
        printf("\n\n Server running and waiting for connection \n");                                //informacja o tym ze server wystartowal i czeka na polaczenie
        clintConnect = accept(clintListen, (struct sockaddr*)NULL, NULL);

        clock = time(NULL);
        snprintf(dataSending, sizeof(dataSending), "%.24s\r\n", ctime(&clock));                    //Napisanie wiadomosci
        write(clintConnect, dataSending, strlen(dataSending));

        close(clintConnect);
        sleep(1);
    }
    
    
   
    return 0;
}

