// these all functions assign the results to global variables witch are used inside the main menus and are void



//client functions
//declaring a function to produce wanted contents in a proper format with concatenating the wanted things to sending buffer
void MyStrcat(char* order, char* channelOrUserName, char* passOrAuthToken);
//declaring a function to make the common using string to zero to use it in the next operation
void MyMemset();
//declaring a function to handle the received buffer and parse it to content and type strings
void CjsonHandler();



//server functions

//defining a function for checking if the registering username or channel name already
//exists and returning the error message by errorOrsuccess messsage function defined
void checkingExistenceBeforeRegistration();
//like above this function checks for existence before operation with opening the file
void checkingExistenceBeforeOperations();

//defining a function for checking authtoken this function works depended on the indexOfReqUserFinder function
void authTokenChecker();
//defining a function for finding index of reqUser by the authToken
void indexOfReqUserFinder();
//defining a function to check if reqUser is on any channel and sending proper message if not
void isReqUserOnAnyChannel();
//defining a function for handling the string received by the req user and works on the place of comma and separates the content
//based on that
void receivedBufferHandlerForThreeParties(int i);
//like above but for two parties reqs
void receivedBufferHandlerForTwoParties(int i);
//defining a function for creating proper error or success message for operations
//this creates an object two strings for content and type and converts it to a string
//and sends it to the client by clients socket
void errorOrSuccessMessageHandler(char* ErrorOrSuccess, char* ProperErrorOrSuccessMessage);
//define a function for getting username and password from username files
//parses the received buffer and gets the user name and password by the tag from the parsed object and puts
//the content in the proper global variables
void cjsonHandlerForUserFiles();
//makes an authToken with random characters and save it to the proper array witch contains the authTokens to
//operate on them when needed and we have the authToken only
//and also sends it to the client for usage of it in the client side
void authMaker();




