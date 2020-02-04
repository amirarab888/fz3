//inculings
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
//#include "cJSON.h"
//#include "cJSON.c"
#include <time.h>
#define MAX 80
#define PORT 12345
#define SA struct sockaddr
#define max 2000
//end of including

//dec variables related to connecting
int server_socket, client_socket;
struct sockaddr_in server, client;
//end

//declaring variables
char token[max];
int numOfOnlineUsers;
char authtokens[max][max];
char usersChannelsNames[max][max];
char usernames[max][max];
char passWord1[max];
int usersCheckedMessages[max];
int numOfChannelsMessages[max];
char containerOfChannelsName;
int indexOfReqUser;
/*cJSON* parsed;
cJSON* usernameJSONString;
cJSON* passwordJSONString;
cJSON *userMainObj;
cJSON *userName;
cJSON *passWord;*/
char userObjString[max];
char messagesFromcChannel[max];
bool is;
char messagesFromChannelString[max];
FILE* filePtr;
char readChannelFilesTemp;
//cJSON* messagesFromChannelParsed;
//cJSON* messArray;
char savingStringFromJSON[max];
//cJSON* messageAddingToArrayJSON;
//cJSON* meesAddingToObjectToArray ;
//cJSON* senderAddingToObjectToArray ;
bool is ;
char readChannelFilesTemp;
char channelMessagesString[max];
char newMessAndSenderObjsString[max];
/*cJSON* parsed;
cJSON* messArray;
cJSON* newMessAndSenderObj;
cJSON* type;
cJSON* newMessArray;
cJSON* messageAndSenderStrinJSONSContainerObj;*/
char sendingString[1000000];
/*cJSON* mainObj;
cJSON* type;
cJSON* content;
cJSON* addingStringToJsonArray;*/
const char bufferErrorOrSuccess[max];
char readFromUserFiles[max];
int i = 0;
char readFromUserFilesTemp;
FILE* filePtr;
/*cJSON* channelMainObj;
cJSON* channelNameJSONString;
cJSON* channelMessageJSONArray;
cJSON* mainObjForErrorOrSuccess;
cJSON* typeErrorOrSuccess;
cJSON* contentErrorOrSuccess;*/
//
//declaring a string to receive the order
char firstBuffer[max];
//


//dec of variables for buffer handler functions
char request[max];
char namesOrMessage[max][max];
char firstNameOrMessage[max];
char authToken[max][max];
char firstAuthToken[max];
//

//prototypes of functions
void myRegister();
void connecct();
void cjsonHandlerForUserFiles();
void myLogin();
void authMaker();
void createChannel();
void joinChannel();
void sendMessage();
void refresh();
void errorOrSuccessMessageHandler(char* ErrorOrSuccess, char* ProperErrorOrSuccessMessage);
void receivedBufferHandlerForTwoParties(int i);
void receivedBufferHandlerForThreeParties(int i);
void checkingExistenceBeforeOperations();
void channelMembers();
void leavingChannel();
void logout();
void indexOfReqUserFinder();
void checkingExistenceBeforeRegistration();
void authTokenChecker();
void isReqUserOnAnyChannel();
void authMaker();
void errorOrSuccessMessageHandler(char* ErrorOrSuccess, char* ProperErrorOrSuccessMessage);
void cjsonHandlerForUserFiles();
//

int main()
{
    //connecting
    connecct();
    //starting a loop to receive the orders with buffer string from the client and operating as long as there are orders
    while(1)
    {
        //accepting and listening to receive the orders
        acceptAndListen();
        //receiving
        recv(client_socket, firstBuffer, sizeof(firstBuffer), 0);
        //going the proper functions with comparing the order request section with the abilities of the server
        if(strncmp(firstBuffer, "register", 8) == 0)
        {
            receivedBufferHandlerForThreeParties(9);
            myRegister();
        }
        else if(strncmp(firstBuffer, "login", 5) == 0)
        {
            receivedBufferHandlerForThreeParties(6);
            printf("\nfirstAuthToken : %s\nfirstName : %s\n", firstAuthToken, firstNameOrMessage);
            myLogin();
            //printf("\nauthToken[numofonline]%s\n", authToken[numOfOnlineUsers - 1]);
            //saving the username in the usernames array and authToken in the authToken array and messagOrName to the
            //namesOrMessage array to use them if we want refresh and we would know the online and joined members
            //strcpy(namesOrMessage[numOfOnlineUsers], firstNameOrMessage);
        }
        else if(strncmp(firstBuffer, "create channel",14) == 0)
        {
            receivedBufferHandlerForThreeParties(15);
            printf("\nfirstnameOrmessage : %s\tfirstAuthToken : %s\n", firstNameOrMessage, firstAuthToken);
            indexOfReqUserFinder();
            printf("\nindex%d\n", indexOfReqUser);
            strcpy(usersChannelsNames[indexOfReqUser], firstNameOrMessage);
            printf("channel name : %s\n", usersChannelsNames[indexOfReqUser]);
            strcpy(namesOrMessage[indexOfReqUser], firstNameOrMessage);
            createChannel();
        }
        else if(strncmp(firstBuffer, "join channel", 12) == 0)
        {
            receivedBufferHandlerForThreeParties(13);
            indexOfReqUserFinder();
            joinChannel();
        }
        else if(strncmp(firstBuffer, "send", 4) == 0)
        {
            receivedBufferHandlerForThreeParties(5);
            printf("\nfirstName : %s\nfirstAuthToken : %s", firstNameOrMessage, firstAuthToken);
            indexOfReqUserFinder();
            strcpy(namesOrMessage[indexOfReqUser], firstNameOrMessage);
            sendMessage();
        }
        else if(strncmp(firstBuffer, "refresh", 7) == 0)
        {
            receivedBufferHandlerForTwoParties(8);
            indexOfReqUserFinder();
            refresh();
        }
        else if(strncmp(firstBuffer, "channel members", 15) == 0)
        {
            receivedBufferHandlerForTwoParties(16);
            indexOfReqUserFinder();
            /*strcpy(namesOrMessage[indexOfReqUser], firstNameOrMessage);
            strcpy(authToken[indexOfReqUser], firstAuthToken);*/
            channelMembers();
        }
        else if(strncmp(firstBuffer, "leave", 5) == 0)
        {
            receivedBufferHandlerForTwoParties(6);
            indexOfReqUserFinder();
            /*strcpy(namesOrMessage[indexOfReqUser], firstNameOrMessage);
            strcpy(authToken[indexOfReqUser], firstAuthToken);*/
            leavingChannel();
        }
        else if(strncmp(firstBuffer, "logout", 6) == 0)
        {
            receivedBufferHandlerForTwoParties(7);
            indexOfReqUserFinder();
            /*strcpy(namesOrMessage[indexOfReqUser], firstNameOrMessage);
            strcpy(authToken[indexOfReqUser], firstAuthToken);*/
            logout();
        }

    }

    closesocket(server_socket);
    return;
}
void connecct()
{
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
    server_socket = socket(AF_INET, SOCK_STREAM, 6);
    if (server_socket == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError() );
    else
        printf("Socket successfully created..\n");

    // Assign IP and port
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    // Bind newly created socket to given IP and verify
    if ((bind(server_socket, (SA *)&server, sizeof(server))) != 0)
    {
        printf("Socket binding failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully bound..\n");
    // Now server is ready to listen and verify
    if ((listen(server_socket, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");




}
void acceptAndListen()
{
    // Accept the data packet from client and verify
    int len = sizeof(client);
    client_socket = accept(server_socket, (SA *)&client, &len);
    if (client_socket < 0)
    {
        printf("Server accceptance failed...\n");
        exit(0);
    }
    else
        printf("Server acccepted the client..\n");

}
void myRegister()
{
    //checking if a client with that user name already exists or not
    checkingExistenceBeforeRegistration();
    //creating file with the name of the user and adding username and password json strings to an userFileMainObj to make a string from it and save it to a file
    /*userMainObj = cJSON_CreateObject();
    userName = cJSON_CreateString(firstNameOrMessage);
    passWord = cJSON_CreateString(firstAuthToken);
    cJSON_AddItemToObject(userMainObj, "username", userName);
    cJSON_AddItemToObject(userMainObj, "password", passWord);
    strcpy(userObjString, cJSON_Print(userMainObj));*/
    char userName1[max];
    strcpy(userName1, firstNameOrMessage);
    strcpy(passWord1, firstAuthToken);
    strcat(passWord1, "\n");
    strcpy(userObjString,"{\n");
    strcat(userObjString,"\"username\":	");
    strcat(userObjString,"\"");
    strcat(userObjString, userName1);
    strcat(userObjString,"\",\n");
    strcat(userObjString,"\"password\":	");
    strcat(userObjString,"\"");
    strcat(userObjString, passWord1);
    strcat(userObjString,"\"\n");
    strcat(userObjString,"}\0");
    filePtr = fopen(firstNameOrMessage, "w");
    fprintf(filePtr, "%s", userObjString);
    fclose(filePtr);
    errorOrSuccessMessageHandler("Success", "");
}
void myLogin()
{
    //checking if the username is registered already
    checkingExistenceBeforeOperations();
    //reading the user saved informations to check if the pass word is true
    cjsonHandlerForUserFiles();
    printf("\nbaade cjson handler for user files\n");
    printf("\passWord1 : %s\nfirstAuthToken%s\n", passWord1, firstAuthToken);
//    printf("passwordJSONString -> valuestring :%s\n", passwordJSONString -> valuestring);
  //  printf("usernameJSONString -> valuestring : %s\n", usernameJSONString -> valuestring);
    //authToken[numOfOnlineUsers]+1
    if(strncmp(passWord1, firstAuthToken, 3) != 0)
    {
        errorOrSuccessMessageHandler("Error", "password not correct");
    }
    else
    {
        authMaker();
        strcpy(usernames[numOfOnlineUsers], firstNameOrMessage);
        strcat(authToken[numOfOnlineUsers] , token);
        //strcpy(authToken[numOfOnlineUsers], token);
        printf("authToken : %s\n", authToken[numOfOnlineUsers]);
        numOfOnlineUsers += 1;
    }

}

void createChannel()
{
    authTokenChecker();
    //printf("\nafter authtoken checker\n");
    checkingExistenceBeforeRegistration();
    //printf("\nafter cehcking existance\n");
    errorOrSuccessMessageHandler("Successful", "");
    //printf("\nafter error message sending\n");
    filePtr = fopen(firstNameOrMessage, "w");
    /*channelMainObj = cJSON_CreateObject();
    channelNameJSONString = cJSON_CreateString(usersChannelsNames[indexOfReqUser]);
    cJSON_AddItemToObject(channelMainObj, "name", channelNameJSONString);
    channelMessageJSONArray = cJSON_CreateArray();
    cJSON_AddItemToObject(channelMainObj, "messages", channelMessageJSONArray);
    strcpy(messagesFromcChannel, cJSON_Print(channelMainObj));*/
    strcpy(messagesFromcChannel, "{");
    strcat(messagesFromcChannel,"\"name\":	\"");
    strcat(messagesFromcChannel, firstNameOrMessage);
    strcat(messagesFromcChannel, "\",\n\"messages\":	[]}\0");
    fprintf(filePtr, "%s", messagesFromcChannel);
    fclose(filePtr);
    //printf("\nchizi ke too file zakhire mishe : %s\n", messagesFromcChannel);
    return;
}
void joinChannel()
{
    authTokenChecker();
    checkingExistenceBeforeOperations();
    strcpy(usersChannelsNames[indexOfReqUser], firstNameOrMessage);
    errorOrSuccessMessageHandler("Successful", "");
    return;
}
void sendMessage()
{
    authTokenChecker();
    isReqUserOnAnyChannel();
    filePtr = fopen(usersChannelsNames[indexOfReqUser], "r");
    //reading the last messages json to use it to compelete the file content
    if(filePtr != 0)
    {

        int j = 0;

        while((readChannelFilesTemp = getc(filePtr)) != EOF)
        {
            messagesFromChannelString[j] = readChannelFilesTemp;
            j++;
        }
        printf("read from channel file : %s", messagesFromChannelString);
    }
    fclose(filePtr);
    filePtr = fopen(usersChannelsNames[indexOfReqUser], "w");
    /*messagesFromChannelParsed = cJSON_Parse(messagesFromChannelString);

    //get the array addr has been made in creating channel section
    messArray = cJSON_GetObjectItem(messagesFromChannelParsed, "messages");
    //making the message JSONSting and add it to the array
    messageAddingToArrayJSON = cJSON_CreateObject();
    meesAddingToObjectToArray = cJSON_CreateString(firstNameOrMessage);
    cJSON_AddItemToObject(messageAddingToArrayJSON, "content",meesAddingToObjectToArray);
    senderAddingToObjectToArray = cJSON_CreateString(usernames[indexOfReqUser]);
    cJSON_AddItemToObject(messageAddingToArrayJSON, "sender",senderAddingToObjectToArray);
    cJSON_AddItemToArray(messArray, messageAddingToArrayJSON);
    //making a string if the json to write it in the file

    strcpy(savingStringFromJSON, cJSON_Print(messagesFromChannelParsed));*/
    char newSaving[2000];
    strcpy(newSaving, ", {\n\"content\":	\"");
    strcat(newSaving, firstNameOrMessage);
    strcat(newSaving, "\",\n\"sender\":	\"");
    strcat(newSaving, usernames[indexOfReqUser]);
    strcat(newSaving,"\"\n		}]\n}\0");
    char* JayeKoorooshe = strrchr(messagesFromChannelString,']');
    char messagesToChannel[1500];
    for(int i =0; i<strlen(newSaving); i++)
    {
        messagesToChannel[i] = newSaving[i];
    }
    int r=0;
    for(r=0; r<strlen(messagesToChannel); r++)
    {
        *(JayeKoorooshe + r) = messagesToChannel[r];
    }
    *(JayeKoorooshe + r) = '\0';
    fprintf(filePtr, "%s", messagesFromChannelString);
    fclose(filePtr);
    //sending success message
    errorOrSuccessMessageHandler("Success", "");
}
void refresh()
{
    authTokenChecker();
    isReqUserOnAnyChannel();
    filePtr = fopen(usersChannelsNames[indexOfReqUser], "r");
    if(filePtr != 0)
    {
        int j = 0;
        while((readChannelFilesTemp = getc(filePtr)) != EOF)
        {
            channelMessagesString[j] = readChannelFilesTemp;
            j++;
        }
    }
    fclose(filePtr);
    printf("read from channel file : %s\n", channelMessagesString);
    /*parsed = cJSON_Parse(channelMessagesString);
    messArray = cJSON_GetObjectItem(parsed, "messages");
    newMessAndSenderObj = cJSON_CreateObject();
    type = cJSON_CreateString("List");
    cJSON_AddItemToObject(newMessAndSenderObj, "type", type);
    newMessArray = cJSON_CreateArray();
    messageAndSenderStrinJSONSContainerObj;
    printf("\nuser checked messages number : %d\n", usersCheckedMessages[indexOfReqUser]);
    for(int i=usersCheckedMessages[indexOfReqUser];; i++)
    {
        messageAndSenderStrinJSONSContainerObj = cJSON_GetArrayItem(messArray,i);
        if(i == usersCheckedMessages[indexOfReqUser]+1)
        {
            usersCheckedMessages[indexOfReqUser] = cJSON_GetArraySize(messArray);
            break;
        }
        cJSON_AddItemToArray(newMessArray, messageAndSenderStrinJSONSContainerObj);
    }
    cJSON_AddItemToObject(newMessAndSenderObj, "content", newMessArray);
    strcpy(newMessAndSenderObjsString, cJSON_Print(newMessAndSenderObj));*/
    strcpy(newMessAndSenderObjsString, "{\n   \"type\":\"List\",\n   \"content\":[\n   ");
    printf("\nCHIE : %s", newMessAndSenderObjsString);
    char* jayeOonAlamata = -2;
    char message1[1500];
    for(int i=0; i<=usersCheckedMessages[indexOfReqUser] +1; i++)
    {
        jayeOonAlamata = strchr(channelMessagesString, '{');
        if(i <= usersCheckedMessages[indexOfReqUser])
            *(jayeOonAlamata) = '%';
    }
    printf("\nchannel messages string : %s\n", channelMessagesString);
    //jayeOonAlamata += 1;
    int j=0;
    while(*(jayeOonAlamata + j) != ']')
    {
        //printf("mohtava : %c", *(jayeOonAlamata));
        message1[j] = *(jayeOonAlamata);
        j += 1;
        jayeOonAlamata += 1;
    }
    strcat(newMessAndSenderObjsString, message1);
    strcat(newMessAndSenderObjsString, "\n]\n}");
    strcat(newMessAndSenderObjsString, jayeOonAlamata);
    printf("\nchizi ke mikhaim befrestim : %s\n", newMessAndSenderObjsString);
    send(client_socket, newMessAndSenderObjsString, sizeof(newMessAndSenderObjsString), 0);
}

void channelMembers()
{
    //mainObj = cJSON_CreateObject();
    authTokenChecker();
    isReqUserOnAnyChannel();
    /*type = cJSON_CreateString("List");
    cJSON_AddItemToObject(mainObj, "type", type);
    content = cJSON_CreateArray();
    //if auth is ok then find the index and make the proper json which contains the type object and content array witch itself contains strings
     //= cJSON_CreateString();
    for(int i=0; i<numOfOnlineUsers; i++)
    {
        if(strcmp(usersChannelsNames[i], usersChannelsNames[indexOfReqUser]) == 0)
        {
            addingStringToJsonArray = cJSON_CreateString(usernames[i]);
            cJSON_AddItemToArray(content, addingStringToJsonArray);
        }
    }
    //adding the json array to mainobj
    cJSON_AddItemToObject(mainObj, "content", content);
    strcpy(sendingString, cJSON_Print(mainObj));*/
    strcpy(sendingString, "{\n   \"type\":\"List\",\n   \"content\":[");
    for(int u=0; u<=numOfOnlineUsers; u++)
    {
        if(strcmp(usersChannelsNames[u], usersChannelsNames[indexOfReqUser]) == 0)
        {
            strcat(sendingString, "\"");
            strcat(sendingString, usernames[u]);
            strcat(sendingString, "\",");
        }
    }
    strcat(sendingString, "]}");
    printf("\nchizi ke mikham bedim : %s", sendingString);
    char* jayeOON = -3;
    jayeOON = strchr(sendingString, ']');
    *(jayeOON - 1) = ' ';
    send(client_socket, sendingString, sizeof(sendingString), 0);
}
void leavingChannel()
{
    authTokenChecker();
    //checking if the requser is in any channel
    isReqUserOnAnyChannel();
    //deleting channel name from the arrays supporting them
    usersChannelsNames[indexOfReqUser][0] = '\0';
    //sending the proper json for success
    errorOrSuccessMessageHandler("Successful", "");
}

void logout()
{
    authTokenChecker();
    //deleting the authtoken to make the user imossible using it again
    authtokens[indexOfReqUser][0] = '\0';
    usersCheckedMessages[indexOfReqUser] = 0;
    //sending the proper json if success
    errorOrSuccessMessageHandler("Successful", "");
}

//defining a function for checking if the registering username or channel name already exists and returning the error message by errorOrsuccess messsage function defined
void checkingExistenceBeforeRegistration()
{
    filePtr = fopen(firstNameOrMessage, "r");
    if(filePtr != 0)
    {
        errorOrSuccessMessageHandler("Error", "this name has been token already");
        exit(0);
    }
}

void checkingExistenceBeforeOperations()
{
    filePtr = fopen(firstNameOrMessage, "r");
    if(filePtr == 0)
    {
        errorOrSuccessMessageHandler("Error", "this name doesnt exist");
        exit(1);
    }
}

//defining a function for checking authtoken
void authTokenChecker()
{
    /*is = false;
    printf("\nfirstAuthToken : %s\t")
    for(int i=0; i<=numOfOnlineUsers; i++)
    {
        if(strncmp(firstAuthToken, authToken[indexOfReqUser],10) == 0)
        {
            is = true;
        }
    }
    if(is == false)
    {
        errorOrSuccessMessageHandler("Error", "authToken not valid");
        exit(1);
    }*/
    if(indexOfReqUser < 0)
    {
        errorOrSuccessMessageHandler("Error", "authToken not valid");
    }
}
//defining a function for finding index of reqUser by the authToken
void indexOfReqUserFinder()
{
    for(int i=0; i<numOfOnlineUsers; i++)
    {
        printf("\navvli : %s\tdovvome : %s\n", firstAuthToken, authToken[i]);
        if(strncmp(firstAuthToken, authToken[i], 5) == 0)
        {
            indexOfReqUser = i;
            return;
        }
    }
    indexOfReqUser = -100;
}
//defining a function to check if reqUser is on any channel and sending proper message if not
void isReqUserOnAnyChannel()
{
    if(usersChannelsNames[indexOfReqUser][0] == '\0')
    {
        errorOrSuccessMessageHandler("Error", "your not on any channel");
    }
}
//defining a function for handling the string received by the req user
void receivedBufferHandlerForThreeParties(int i)
{
    //getting the user name channel name authToken and anything given
    int j = 0;
    while(firstBuffer[i] != ',')
    {
        firstNameOrMessage[j] = firstBuffer[i];
        i++;
        j++;
    }
    firstNameOrMessage[j] = '\0';
    i+=2;
    int y=0;
    while(firstBuffer[i] != '\0')
    {
        firstAuthToken[y] = firstBuffer[i];
        i++;
        y++;
    }
    firstAuthToken[y] = '\0';
}
void receivedBufferHandlerForTwoParties(int i)
{
    int y=0;
    while(firstBuffer[i] != '\0')
    {
        firstAuthToken[y] = firstBuffer[i];
        i++;
        y++;
    }
    firstAuthToken[y] = '\0';
}
//defining a function for creating proper error or success message for operations
void errorOrSuccessMessageHandler(char* ErrorOrSuccess, char* ProperErrorOrSuccessMessage)
{
    /*cJSON* mainObjForErrorOrSuccess = cJSON_CreateObject();
    cJSON* typeErrorOrSuccess = cJSON_CreateString(ErrorOrSuccess);
    cJSON_AddItemToObject(mainObjForErrorOrSuccess, "type", typeErrorOrSuccess);
    cJSON* contentErrorOrSuccess = cJSON_CreateString(ProperErrorOrSuccessMessage);
    cJSON_AddItemToObject(mainObjForErrorOrSuccess, "content", contentErrorOrSuccess);
    strcpy(bufferErrorOrSuccess, cJSON_Print(mainObjForErrorOrSuccess));*/
    strcpy(bufferErrorOrSuccess, "{\"type\":\"");
    strcat(bufferErrorOrSuccess, ErrorOrSuccess);
    strcat(bufferErrorOrSuccess, "\",\"content\":\"");
    strcat(bufferErrorOrSuccess, ProperErrorOrSuccessMessage);
    strcat(bufferErrorOrSuccess, "\"}");
    printf("\nchizi ke mifreste barash : %s\n", bufferErrorOrSuccess);
    send(client_socket, bufferErrorOrSuccess, sizeof(bufferErrorOrSuccess), 0);
}
//define a function for getting username and password from username files

void cjsonHandlerForUserFiles()
{
    filePtr = fopen(firstNameOrMessage, "r");
    i = 0;
    while((readFromUserFilesTemp = getc(filePtr)) != EOF)
    {
        readFromUserFiles[i] = readFromUserFilesTemp;
        i++;
    }
    /*parsed = cJSON_Parse(readFromUserFiles);
    usernameJSONString = cJSON_GetObjectItem(parsed, "username");
    passwordJSONString = cJSON_GetObjectItem(parsed, "password");*/
    //strcpy(namesOrMessage, usernameJSONString -> valuestring);
    //strcpy(authToken, passwordJSONString -> valuestring);
    char* jayeOON = -2;
    for(int i=0; i<7; i++)
    {
        jayeOON = strchr(readFromUserFiles, '"');
        if(i<6)
        {
            *(jayeOON) = '0';
        }
    }
    jayeOON += 1;
    printf("\n*(jayeOON : %c\n", *(jayeOON));
    int p = 0;
    memset(passWord1, 0, sizeof(passWord1));
    while(*(jayeOON) != ' ' && *(jayeOON) != '"')
    {
        printf("\njayeOON : %c\n", *(jayeOON));
        passWord1[p] = *(jayeOON);
        p += 1;
        jayeOON += 1;
    }
    passWord1[p] = '\0';
    fclose(filePtr);
}

void authMaker()
{
    srand(time(0));
    for(int i=0; i<= 32; i++)
    {
        token[i] = '\0';
    }
    for(int i=0; i<32; i++)
    {
        token[i] = rand()%58 + 35;
    }
    token[32] = '\0';
    errorOrSuccessMessageHandler("AuthToken", token);
}
