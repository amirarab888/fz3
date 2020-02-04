#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "cJSON.h"
#include "cJSON.c"
#define MAX 1000
#define PORT 12345
#define SA struct sockaddr


char buffer[MAX];
char authToken[MAX];
char userName[MAX];
char channelName[MAX];
char pass[MAX];
char message[MAX];

cJSON* parsed = 0;
cJSON* content = 0;
cJSON* type = 0;


void MainMenu();
void CjsonHandler();
void UserMenu();
void MyStrcat();
void MyMemset();
void SocketMaker();
void communicationMenu();
// Function designed for chat between client and server.
void chat(int server_socket)
{
	char buffer[MAX];
	int n;
	while (true) {
		memset(buffer, 0, sizeof(buffer));
		printf("Enter your message: ");
		n = 0;

		// Copy client message to the buffer
		while ((buffer[n++] = getchar()) != '\n')
			;

		// Send the buffer to server
		send(server_socket, buffer, sizeof(buffer), 0);
		memset(buffer, 0, sizeof(buffer));

		// Read the message from server and copy it to buffer
		recv(server_socket, buffer, sizeof(buffer), 0);

		// Print buffer which contains the server message
		printf("From server: %s", buffer);

		// If the message starts with "exit" then client exits and chat ends
		if ((strncmp(buffer, "exit", 4)) == 0) {
			printf("Client stopping...\n");
			return;
		}
	}
}
//going to proper menus
int main()
{
    UserMenu();
    MainMenu();
    communicationMenu();
}
//declaring a function for communication menu
void communicationMenu()
{
    while(1)
    {
        printf("1: send message\n2: refresh\n3: channel members\n4: Leave channel\n");
        int gozine = 0;
        while(gozine != 1 && gozine != 2 && gozine != 3 && gozine != 4)
        {
            printf("Choose a valid option\n");
            scanf("%d", &gozine);
        }
        if(gozine == 1)
        {
            MyMemset();
            printf("Enter your message:\n");
            scanf("%s", &message);
            MyStrcat("send", message, authToken);
            SocketMaker();
            //CjsonHandler();
            if(buffer[9] == 'E')
               printf("Sending unsuccessful");

        }
        if(gozine == 2)
        {
            MyMemset();
            //printf("Enter channel name:\n");
            //scanf("%s", &userName);
            MyStrcat("refresh", 0, authToken);
            SocketMaker();
            //printf("\nbuffer : %s\n", buffer);
            //CjsonHandler();
            //char* jj = 0;
            //jj = strchr(buffer, "List");
            //if(jj != 0)
            //{
                char mess1[1500];
                char sender1[100];
                char* ja = -2;
                for(int i=0; i<9 ;i++)
                {
                    ja = strchr(buffer, '"');
                    *(ja) = '%';
                }
                ja += 1;
                int o = 0;
                while(*(ja) != '"')
                {
                    mess1[o] = *(ja);
                    ja += 1;
                    o += 1;
                }
                mess1[o] = '\0';
                for(int i=0; i<4 ;i++)
                {
                    ja = strchr(buffer, '"');
                    *(ja) = '%';
                }
                ja += 1;
                int h = 0;
                while(*(ja) != '"')
                {
                    sender1[h] = *(ja);
                    ja += 1;
                    h += 1;
                }
                sender1[h] = '\0';
                printf("%s : %s\n", sender1, mess1);
                while(1)
                {
                    ja = strchr(buffer, '"');
                    if(ja != 0)
                    {
                        for(int i=0; i<4 ;i++)
                    {
                        ja = strchr(buffer, '"');
                        *(ja) = '%';
                    }
                    ja += 1;
                    o = 0;
                    while(*(ja) != '"')
                    {
                        mess1[o] = *(ja);
                        ja += 1;
                        o += 1;
                    }
                    mess1[o] = '\0';
                    for(int i=0; i<4 ;i++)
                    {
                        ja = strchr(buffer, '"');
                        *(ja) = '%';
                    }
                    ja += 1;
                    h = 0;
                    while(*(ja) != '"')
                    {
                        sender1[h] = *(ja);
                        ja += 1;
                        h += 1;
                    }
                    sender1[h] = '\0';
                    printf("%s : %s\n", sender1, mess1);


                    }
                    else
                        break;

                //}
                //printf("RATFFF");
               /* int contentSize = cJSON_GetArraySize(content);
                //if(contentSize > 1)
                //{
                    for(int i=0; i<contentSize; i++)
                    {
                        cJSON *paresdContentToIndividualJasonsFromArrayOfJsons = cJSON_GetArrayItem(content,i);
                        cJSON *sender = cJSON_GetObjectItem(paresdContentToIndividualJasonsFromArrayOfJsons,"sender");
                        printf("%s :", sender->valuestring);
                        cJSON *message = cJSON_GetObjectItem(paresdContentToIndividualJasonsFromArrayOfJsons,"content");
                        printf("%s\n", message->valuestring);
                    }
                //}*/
                /*else
                {
                    for(int i=0; i<contentSize; i++)
                    {
                        cJSON* people = cJSON_GetArrayItem(content, i);
                        printf("%s", people->valuestring);
                    }
                }*/
            }
            printf("\nBAAAAAAAA\n");
        }
        if(gozine == 3)
        {
            MyMemset();
            //printf("Enter channel name:\n");
            //scanf("%s", &userName);
            MyStrcat("channel members", 0, authToken);
            SocketMaker();
            CjsonHandler();
            if(!strcmp(type->valuestring,"List"))
            {
                //printf("RATFFF\n");
                int contentSize = cJSON_GetArraySize(content);
                //printf("RATFFF\n");
                //if(contentSize > 1)
                //{
                    for(int i=0; i<contentSize; i++)
                    {
                        //printf("RATFFFto for\n");
                        cJSON *paresdContentToIndividualJasonsFromArrayOfJsons = cJSON_GetArrayItem(content,i);
                        //printf("RATFFF to getarray\n");
                        //cJSON *sender = cJSON_GetObjectItem(paresdContentToIndividualJasonsFromArrayOfJsons,"sender");
                        printf("%s :\n", paresdContentToIndividualJasonsFromArrayOfJsons->valuestring);
                       // cJSON *message = cJSON_GetObjectItem(paresdContentToIndividualJasonsFromArrayOfJsons,"content");
                        //printf("%s\n", message->valuestring);
                    }
                //}
                /*else
                {
                    for(int i=0; i<contentSize; i++)
                    {
                        cJSON* people = cJSON_GetArrayItem(content, i);
                        printf("%s", people->valuestring);
                    }
                }*/
            }
        }
        if(gozine == 4)
        {
            MyMemset();
            MyStrcat("leave", 0, authToken);
            SocketMaker();
            //CjsonHandler();
            if(buffer[9] == 'S')
               MainMenu();
            else
                printf("exiting channel unsuccessful");
        }

    }
    return;
}
//declaring the main menu
void MainMenu()
{
    while(1)
    {
        printf("1: Create channel\n2: Join channel\n3: Logout\n");
        int gozine = 0;
        while(gozine != 1 && gozine != 2 && gozine != 3)
        {
            printf("Choose a valid option\n");
            scanf("%d", &gozine);
        }
        if(gozine == 1)
        {
            MyMemset();
            printf("Enter channel name:\n");
            scanf("%s", &channelName);
            MyStrcat("create channel", channelName, authToken);
            SocketMaker();
            //CjsonHandler();
            printf("\nbuffer : %s", buffer);
            if(buffer[9] == 'E')
               printf("Creating channel unsuccessful");
            else
                break;

        }
        if(gozine == 2)
        {
            MyMemset();
            printf("Enter channel name:\n");
            scanf("%s", &channelName);
            MyStrcat("join channel", channelName, authToken);
            SocketMaker();
            //CjsonHandler();
            if(buffer[9] == 'S')
               break;
            else
                printf("joining in unsuccessful");
        }
        if(gozine == 3)
        {
            MyMemset();
            MyStrcat("logout", 0, authToken);
            SocketMaker();
            //CjsonHandler();
            if(buffer[9] == 'S')
               UserMenu();
            else
                printf("loging out unsuccessful");
        }

    }
    return;
}
//declaring the user menu
void UserMenu()
{
    while(1)
    {
        printf("Account Menu\n1: Register\n2: Login\n");
        int gozine = 0;
        while(gozine != 1 && gozine != 2)
        {
            printf("Choose a valid option\n");
            scanf("%d", &gozine);
        }
        if(gozine == 1)
        {
            MyMemset();
            printf("Enter username:\n");
            scanf("%s", &userName);
            printf("Enter pass:\n");
            scanf("%s", &pass);
            MyStrcat("register", userName, pass);
            SocketMaker();
            //CjsonHandler();
            printf("\nbuuffer : %s\n", buffer);
            if(buffer[10] == 'E')
               printf("Creating account unsuccessful");

        }
        if(gozine == 2)
        {
            MyMemset();
            printf("Enter username:\n");
            scanf("%s", &userName);
            printf("Enter pass:\n");
            scanf("%s", &pass);
            MyStrcat("login", userName, pass);
            SocketMaker();
            printf("\nbuffer : %s\n", buffer);
            //CjsonHandler();
            if(buffer[9] == 'A')
            {
                int g = 31;
                int i =0;
                while(buffer[g] != '"')
                {
                    authToken[i] = buffer[g];
                    g++;
                    i++;

                }
                authToken[i] = '\0';
                break;
            }
            else
                printf("Longing in unsuccessful\n");
        }
    }
    return;
}
//declaring a function to produce wanted contents in a proper format
void MyStrcat(char* order, char* channelOrUserName, char* passOrAuthToken)
{
    strcat(buffer, order);
    strcat(buffer, " ");
    if(channelOrUserName != 0)
    {
        strcat(buffer, channelOrUserName);
        strcat(buffer, ", ");
    }
    strcat(buffer, passOrAuthToken);
    strcat(buffer, "\n");
}
//declaring a function to make the common using string to zero to use it in the next operation
void MyMemset()
{
    memset(buffer, 0, sizeof(buffer));
    memset(channelName, 0, sizeof(buffer));
    memset(userName, 0, sizeof(buffer));
    memset(pass, 0, sizeof(buffer));
    memset(message, 0, sizeof(buffer));
}
//declaring a function to handle the received buffer and parse it to content and type strings
void CjsonHandler()
{
    parsed = cJSON_Parse(buffer);
    content = cJSON_GetObjectItem(parsed, "content");
    type = cJSON_GetObjectItem(parsed, "type");
    //printf("RATFFF");


}
void SocketMaker()
{
    int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;

	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

	// Function for chat
	//chat(client_socket);
	//printf("%s", buffer);
	//printf("taghablesed");
	send(client_socket, buffer, sizeof(buffer), 0);
	//printf("baadesend\n");
	memset(buffer, 0, sizeof(buffer));
	//printf("bbadememset\n");
    recv(client_socket, buffer, sizeof(buffer), 0);
    //printf("baadereceive");
	// Close the socket
	closesocket(client_socket);
}
