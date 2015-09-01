#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>

#define MAXLEVEL 10
using namespace std;

int isAvailable(char command[30], int currentLevel);

struct displayString
{

    char nameOfFile[30];
    char content[1200];

};



class ds
{
public :
    static displayString dpString[10][10];
    static int noOfStrings[10];
    static char passwords[10][30] ;
    static char username[10][30] ;
    static int currentLevel ;
    static bool playing;

public:
    static int getNoOfStrings(int level)
    {
        return noOfStrings[level-1];
    }

    static displayString getDisplayString(int level,int index)
    {
        return dpString[level-1][index];
    }


    static void trim(char str[]){
        int j=0;
        for(int i=0;i<strlen(str);i++){
            if(str[i] == ' '){
                j++;
            }
            else
                break;
        }
        if(j>0){
            for(int i=0;i<=strlen(str) - j;i++)
                str[i] = str[j+i];

        }
        j=0;
        for(int i=strlen(str)-1;i>=0;i--){
            if(str[i] == ' '){
                j++;
            }
            else
                break;
        }
        if(j>0){
            str[strlen(str) - j ]= '\0';
        }



    }

};
int ds::noOfStrings[10] = {0,0,0,0,0,0,0,0,0};
displayString  ds::dpString[10][10] = {{}};
char ds::passwords[10][30] = {};
char ds::username[10][30] = {};
int ds::currentLevel =1;
bool ds::playing = true;

class Command
{
protected:
    char mainCommand[30],message[100];

    int supportedLevels[10];
    int noOfLevels;

public:
    Command()
    {
        noOfLevels = 0;
    }

    bool isAvailable(int level)
    {
        for(int i=0; i<noOfLevels; i++)
        {
            if(supportedLevels[i] == level)
            {
                return true;
            }
        }
        return false;
    }

    void addSupportedLevel(int level)
    {
        for(int i=0; i<noOfLevels; i++)
        {
            if(supportedLevels[i] == level)
            {
                break;
            }
        }
        supportedLevels[noOfLevels] = level;
        noOfLevels++;
    }

    virtual void performCommand(char command[],int level)
    {

    }
    virtual bool checkValidity(char fullcommand[],int level)
    {

    }
    void getMainCommand(char str[])
    {
        strcpy(str,mainCommand);
        return;
    }


    void getMessage(char str[])
    {
        strcpy(str,message);
        return;
    }

};

class HelpCommand : public Command
{

    Command *cList[10];
    int noOfCommands;

public:


    void setCommandList(Command *c[10],int noOfCommands)
    {
        this->noOfCommands = noOfCommands;
        for(int i=0; i<noOfCommands; i++)
        {
            cList[i] = c[i];
        }
    }
    HelpCommand()
    {

        strcpy(mainCommand,"help");
        strcpy(message,"to view all the available commands");
        for(int i=1; i<=MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }

    }

    void performCommand(char command[],int level)
    {

        char tempCommand[100];
        if(checkValidity(command,level) == 1)
        {
            for(int i =0; i<noOfCommands; i++)
            {
                cList[i]->getMainCommand(tempCommand);
                printf("\n %s -- ",tempCommand);
                cList[i]->getMessage(tempCommand);
                printf("%s",tempCommand);
            }
            printf("\n");
        }
        else
        {
            printf("\tUsage : help");
        }

        return;

    }

    bool checkValidity(char fullCommand[],int level)
    {
        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        if(strcmp(remainingCommand,"") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }



};

class ListCommand : public Command
{

public :

    ListCommand()
    {
        strcpy(mainCommand,"list");
        strcpy(message,"to list all files present in current stage");
        for(int i=1; i<= MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }
    }


    void performCommand(char command[],int level)
    {
        if(checkValidity(command,level) == 1)
        {
            for(int i=0; i<ds::getNoOfStrings(level); i++)
            {
                displayString dtemp = ds::getDisplayString(level,i);
                printf("\t %s",dtemp.nameOfFile);

            }
        }
        else
        {
            printf("\tUsage : list");
        }

    }

    bool checkValidity(char fullCommand[30],int level)
    {

        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        if(strcmp(remainingCommand,"") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }





};




class ViewCommand : public Command
{
private:
    int value;

public :

    ViewCommand()
    {
        strcpy(mainCommand,"view");
        strcpy(message,"to open a file or mail");
        for(int i=1; i<= MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }
        value = -1;
    }

    void performCommand(char command[],int level)
    {
        if(checkValidity(command,level) == 1)
        {
            return;
        }
        else
        {
            printf("\tUsage : view <filename>");
        }

    }

    bool checkValidity(char fullCommand[30],int level)
    {

        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        for(int i=0; i<ds::getNoOfStrings(level); i++)
        {
            displayString dtemp = ds::getDisplayString(level,i);
            if(strcmp(remainingCommand,dtemp.nameOfFile)==0)
            {
                printf("%s",dtemp.content);
                return true;
            }

        }
    }


};


class PasswordCommand : public Command
{


public:

    PasswordCommand()
    {
        strcpy(message,"Enter Username , password and pass the level");
        strcpy(mainCommand,"gateway");
        for(int i=1; i<=MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }

    }

    void performCommand(char command[],int level)
    {
        char pass[30] ="",user[30]="";
        char tempCommand[20];
        if(checkValidity(command,level) == 1)
        {
            printf("\nEnter Username :");
            fgets(user,sizeof(user),stdin);

            printf("Enter Password :");
            fgets(pass,sizeof(pass),stdin);
            for(int j=0; j<strlen(pass); j++)
            {
                printf("\b");
            }
            checkpassword(user,pass,level);

        }
        else
        {
            printf("\tUsage : password");
        }

        return;

    }

    bool checkValidity(char fullCommand[],int level)
    {
        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        if(strcmp(remainingCommand,"") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }


    void checkpassword(char user[],char pass[],int level)
    {

        pass[strlen(pass)-1] = '\0';
        user[strlen(user)-1] = '\0';
        ds::trim(user);
        ds::trim(pass);

        if(user == string(ds::username[level-1]))
        {
            if(pass == string(ds::passwords[level-1]))
            {
                printf("\nAccess Granted \n welcome ");
                ds::currentLevel++;

            }
            else
            {
                printf("Access Denied !!!!!!!!!!!!!!!!!");
            }

        }
        else
        {
            printf("Access Denied !!!!!!!!!!!!!!!!!!!!");
        }

    }

} p;


class CurrentCommand : public Command
{

public:

    CurrentCommand()
    {

        strcpy(mainCommand,"current");
        strcpy(message,"to know in which stage you are now");
        for(int i=1; i<=MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }

    }

    void performCommand(char command[],int level)
    {

        if(checkValidity(command,level) == 1)
        {
            printf("Current Stage : %d",ds::currentLevel);
        }
        else
        {
            printf("\tUsage : help");
        }

        return;

    }

    bool checkValidity(char fullCommand[],int level)
    {
        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        if(strcmp(remainingCommand,"") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
} cv;


class ExitCommand: public Command
{

public:



    ExitCommand()
    {

        strcpy(mainCommand,"exit");
        strcpy(message,"to exit from the hacking session");
        for(int i=1; i<=MAXLEVEL; i++)
        {
            addSupportedLevel(i);
        }

    }

    void performCommand(char command[],int level)
    {

        char tempCommand[100],quit;
        if(checkValidity(command,level) == 1)
        {
            printf("Do you really wanna quit (Y|N)");
            scanf("%c",&quit);
            if(quit == 'y' || quit == 'Y')
            {
                ds::playing = false;
            }
        }
        else
        {
            printf("\tUsage : exit");
        }

        return;

    }

    bool checkValidity(char fullCommand[],int level)
    {
        char mainCommand2[30],remainingCommand[30]="";
        sscanf(fullCommand,"%s %s",mainCommand2,remainingCommand);
        if(strcmp(remainingCommand,"") == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

    }



} e;


void initilizeCommands();
void initilizeStrings();

HelpCommand h;
ListCommand l;
ViewCommand v;
int noOfCommands ;
Command *c[10] ;

char terminalString[20] = "HackSim$ ";

int main()
{
    initilizeCommands();
    initilizeStrings();
    char inputCommand[30],command[10];
    int commandNo;

    printf("\n\nHello, Welcome to invenio security space, Im dave, the human resource officer of Invenio.");
    printf(" We deals with penetrating and accessing the information for our clients from other servers without leaving any mark,");
    printf(" or to be more precise, we hacks into other systems\n\n");
    printf("We are in need of those personnels who possess the wonderful ability to hack into any other system. \nIf you think, you are ");
    printf("awesome enough to join our entreprise, \n\nplease press Y AND <ENTER>, don't hesitate to press N AND <ENTER> if you are scared enough to be a man. \n By the Way you can access the help menu by typing help.");
    char ch ;
    do
    {
        scanf("%c",&ch);
        fflush(stdin);
        switch(ch)
        {
        case 'y':
        case 'Y':
            break;
        case 'n':
        case 'N':
            return 1;
        default:
            ch = 'r';
            printf("\n\n\nPlease Enter Y | N  <ENTER>");

        }
    }
    while(ch=='r');
    ch = getchar();
    fseek(stdin,0,SEEK_END);
    while(ds::playing)
    {

        strcpy(inputCommand,"");

        fflush(stdin);
        printf("\n%s",terminalString);
        fgets(inputCommand,30, stdin);
        sscanf(inputCommand,"%s ",command);
        if((commandNo = isAvailable(command,ds::currentLevel)) >= 0 )
        {
            //commad is valid
            c[commandNo]->performCommand(inputCommand,ds::currentLevel);
        }
        else
        {
            //command is not available
            printf("See help for available commands");
        }

        if(ds::currentLevel > 10)
        {
            printf("\nCongratulations.... You have successfully hacked all accounts");
            printf("\nNow safely exit from the system...");
            ds::playing = false;
        }
    }

    printf("Successfully Exited.........");
    printf("\n\n\n Level Cleared : %d\n\n",ds::currentLevel -1 );

}



int isAvailable(char command[30], int currentLevel)
{
    char mainCommand[30];
    for(int i=0; i<noOfCommands; i++)
    {

        c[i]->getMainCommand(mainCommand);
        if(strcmp(mainCommand,command) == 0)
        {
            return i;
        }
    }
    return -1;
}

void initilizeCommands()
{

    c[0] = &h;
    c[1] = &l;
    c[2] = &v;
    c[3] = &p;
    c[4] = &cv;
    c[5] = &e;
    noOfCommands = 6;

    h.setCommandList(c,noOfCommands);

}

void initilizeStrings()
{


    ds::noOfStrings[0] = 1;
    strcpy(ds::dpString[0][0].nameOfFile,"welcomefile");
    strcpy(ds::dpString[0][0].content,"\n Hey, its John here, am your project lead, your objective is to sneak into the potenzia enterprise and get us the password of their Chief Mike Yurgon.");
    strcat(ds::dpString[0][0].content,"\n We had a priliminary investigation about the staff in potenzia and we learned that their, receptionist Alice is very novice in computers.\n May be you can hack into her system easily\n");
    strcat(ds::dpString[0][0].content,"\n\n*The help - gives you all the available commands and their use. and by the way, All the best, kid\n");


    ds::noOfStrings[1] = 3;//alice

    strcpy(ds::dpString[1][0].nameOfFile,"readme");
    strcpy(ds::dpString[1][0].content,"The Day.\n \t Ah, Just another tiring day.\n i dont know why these people are asking for everything even though they knows everything? such a morons\n");
    strcpy(ds::dpString[1][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[1][1].content,"Khaleesi :- \n Hey Alice, How you doing? \n looks like Dave got something on you. \n he is really bothering me about the details about you. \n he even asked me for your personal number, but not to worry i've adjusted it with your work email. and by the way, he is damn crazy about some football club. \n \n \n David O'shea :- Hello Alice, Hope you are doing well. I just wanna let you know that i got two realmadrid match passes for tonight, so why dont you come along? \n it will be fun.  ");
    strcpy(ds::dpString[1][2].nameOfFile,"Sent");
    strcpy(ds::dpString[1][2].content,"Khaleesi:- \n Oh dear, David Just mailed me, sounds like he is paranoid. Im gonna cut him off.\n David :- \n Hello David, i do appreciate your kindness to invite me. but i have some urgent work to do tonight. \n Sorry. ");

    ds::noOfStrings[2] = 3;//david

    strcpy(ds::dpString[2][0].nameOfFile,"AccountsSteve");
    strcpy(ds::dpString[2][0].content,"\n TA - 3000 \n VPS - 10000 \n Azure - 40000 \n");
    strcpy(ds::dpString[2][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[2][1].content,"James Huffleton :- \n Oh man, seriously? from where you get that? \n thats awesome dude. and mean while, dude have a look at Warren Buffet's annual speech. he is insanely cool. such an awesome guy. he is a pioneer man, am damn obsessed with him.\n \n Alex :- \n Hey nerdo, whats up with all the fuss? heard that you tried your share on Alice? ha ha dont worry fella, it happens. ");
    strcpy(ds::dpString[2][2].nameOfFile,"Sent");
    strcpy(ds::dpString[2][2].content,"James Huffleton :- \n hey man, how you doing? 've got two passes for realmadrid match. wanna join?\n ");

    ds::noOfStrings[3] = 4;//james

    strcpy(ds::dpString[3][0].nameOfFile,"TheInvestor");
    strcpy(ds::dpString[3][0].content,"Oh man, this guy is insanely cool. how on earth he can produce things like that? \n he is playing with numbers as if harry potter does with charms");
    strcpy(ds::dpString[3][1].nameOfFile,"Shayneward");
    strcpy(ds::dpString[3][1].content,"i dont understand. Why on earth Khaleesi is sending me shaynewards lyrics? \n man this is confusing. Still, those lines are really romantic.");
    strcpy(ds::dpString[3][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[3][1].content,"Khaleesi:- \n If our love was a fairy tale \n I would charge in and rescue you \n On a yacht baby we would sail \n To an island where we'd say I do - Shayeward\n ");
    strcpy(ds::dpString[3][2].nameOfFile,"Sent");
    strcpy(ds::dpString[3][2].content,"David O'shea :- \n Oh man, seriously? from where you get that? \n thats awesome dude. and mean while, dude have a look at Warren Buffets annual speech. he is insanely cool. such an awesome guy. he is a pioneer man, am damn obsessed with him.\n");

    ds::noOfStrings[4] = 3;//khaleesi

    strcpy(ds::dpString[4][0].nameOfFile,"Myjude");
    strcpy(ds::dpString[4][0].content,"Oh my god, everytime he looks at me its like am melting. That awesome feeling when he looks at me. oh My jude, i want you with me. My james.");
    strcpy(ds::dpString[4][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[4][1].content,"Rika Yunita:- \n Hey, whats your program for this summer vacation? \n heard that you are going to visit malaysia with your friends.\n if thats the case, come to indonesia as well. \n Am sure that you gonna love my country. \n As you know that am from indonesia, there are lots of areas, which you cant even imagine in your place, and i tell you, indonesia wont ever disappoint you. \n ");
    strcpy(ds::dpString[4][2].nameOfFile,"Sent");
    strcpy(ds::dpString[4][2].content,"James Huffleton:- \n If our love was a fairy tale \n I would charge in and rescue you \n On a yacht baby we would sail \n To an island where we'd say I do - Shayeward\n ");

    ds::noOfStrings[5] = 3;//rika

    strcpy(ds::dpString[5][0].nameOfFile,"MyBooks");
    strcpy(ds::dpString[5][0].content,"jules verne \n Antony Chekhov \n Alexandar Duma");
    strcpy(ds::dpString[5][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[5][1].content,"Khaleesi:-\n hey dear, thank you for inviting me to your country. \n Let me assure you that i will come to your place. \n Thanks.");
    strcpy(ds::dpString[5][2].nameOfFile,"Sent");
    strcpy(ds::dpString[5][2].content,"Khaleesi:- \n Hey, whats your program for this summer vacation? \n heard that you are going to visit malaysia with your friends.\n if thats the case, come to indonesia as well. \n Am sure that you gonna love my country. \n As you know that am from indonesia, there are lots of areas, which you cant even imagine in your place, and i tell you, indonesia wont ever disappoint you. \n \n Alex :- \n Hey ALexie, \n You heard it, didnt you? Most of the fortunes are now letting your fav linux servers go and they are embracing latest Azure from microsoft. \n Man, easy, i can understand your linux, your passion towards it and your wonderful points.\n Dont let this break your heart, linux lover :P");

    ds::noOfStrings[6] = 2;//alex

    strcpy(ds::dpString[6][0].nameOfFile,"Inbox");
    strcpy(ds::dpString[6][0].content,"\nRika Yunita:- \n Hey ALexie, \n You heard it, didnt you? Most of the fortunes are now letting your fav linux servers go and they are embracing latest Azure from microsoft. \n Man, easy, i can understand your linux, your passion towards it and your wonderful points.\n Dont let this break your heart, linux lover :P \n\n Jay Taigon :- \n Hey linux lover. Hope you heard the news, man you still have he chance to let your linux go and join us in the awesome microsoft developer community. \n Dont you still get it? Its our time man. Its Microsoft's time. Look at all those wonderful products made by the pioneers. \n microsoft still stands at the top.");
    strcpy(ds::dpString[6][1].nameOfFile,"Sent");
    strcpy(ds::dpString[6][1].content,"\nGim Amelio:- Hey Gim, if you get some time please teach your kid, jay about the Allen Kay's Quote. Yeah, your favourite's, on talking about his stuff. Just had a look at, The quote you mention always. And man, now i can understand why you admire Allen, so much. \n as you always say, he is a phenom.");

    ds::noOfStrings[7] = 2;//gim

    
    strcpy(ds::dpString[7][0].nameOfFile,"Inbox");
    strcpy(ds::dpString[7][0].content,"\nAlex :- Hey Gim, if you get some time please teach your kid, jay about the Allen Kay's Quote. Yeah, your favourite's, on talking about his stuff. Just had a look at, The quote you mention always. And man, now i can understand why you admire Allen, so much. \n as you always say, he is a phenom. \n\n Mike Yurgon :- \n Hey, Important notice, staff meeting at 9am tomorrow, sharp. \n Punctuality is always appreciated.");
    strcpy(ds::dpString[7][1].nameOfFile,"Sent");
    strcpy(ds::dpString[7][1].content,"\nJay Taigon:- Hey Taigon, Dont let your love and passion towards Microsoft gain you enemies. Alex is a nice guy. just dont mess with him. He loves linux as you are in love with microsoft and its products.");

    ds::noOfStrings[8] = 3;//jay

    strcpy(ds::dpString[8][0].nameOfFile,"KaliLinux");
    strcpy(ds::dpString[8][0].content,"\nRecently, Hilary told me about Kali linux and its wide possibilities. \n  i dont doubt him, but still is it that worth? \n isnt that just a distro with lots of pentesting tools installed? \n There is nothing wonderful in that.\n but the thing i can't understand is, why on earth is he so obsessed with the kali linux? isnt there any other linux models?\n \t Damn him and his kali. ");
    strcpy(ds::dpString[8][1].nameOfFile,"Inbox");
    strcpy(ds::dpString[8][1].content,"\nGim Amelio:- \n Hey Taigon, Dont let your love and passion towards Microsoft gain you enemies. Alex is a nice guy. just dont mess with him. He loves linux as you are in love with microsoft and its products.\n\n Mike Yurgon :- \n Hey, Important notice, staff meeting at 9am tomorrow, sharp. \n Punctuality is always appreciated.");
    strcpy(ds::dpString[8][2].nameOfFile,"Sent");
    strcpy(ds::dpString[8][2].content,"\nAlex:- \n Hey linux lover. Hope you heard the news, man you still have he chance to let your linux go and join us in the awesome microsoft developer community. \n Dont you still get it? Its our time man. Its Microsoft's time. Look at all those wonderful products made by the pioneers. \n microsoft still stands at the top.");

    ds::noOfStrings[9] = 2;//hilary


    strcpy(ds::dpString[9][0].nameOfFile,"Inbox");
    strcpy(ds::dpString[9][0].content,"\nMike Yurgon :- \n Hey, Important notice, staff meeting at 9am tomorrow, sharp. \n Punctuality is always appreciated.");
    strcpy(ds::dpString[9][1].nameOfFile,"Sent");
    strcpy(ds::dpString[9][1].content,"\nMike Yurgon :- \n Hey mike, Yeah punctuality will be appreciated, but what you gonna do? \n Play with your Hitman series, so that you and your Agent47 can enjoy killing people? :P");

    //we need a congratulations note after cracking all levels


    strcpy(ds::username[0],"alice");
    strcpy(ds::username[1],"david");
    strcpy(ds::username[2],"james");
    strcpy(ds::username[3],"khaleesi");
    strcpy(ds::username[4],"rika");
    strcpy(ds::username[5],"alex");
    strcpy(ds::username[6],"gim");
    strcpy(ds::username[7],"jay");
    strcpy(ds::username[8],"hilary");
    strcpy(ds::username[9],"yurgon");



    //use level-1 as index
    strcpy(ds::passwords[0],"password");
    strcpy(ds::passwords[1],"realmadrid");
    strcpy(ds::passwords[2],"warrenbuffet");
    strcpy(ds::passwords[3],"loveyoujames");
    strcpy(ds::passwords[4],"indonesia");
    strcpy(ds::passwords[5],"linux");
    strcpy(ds::passwords[6],"allenkay");
    strcpy(ds::passwords[7],"microsoft");
    strcpy(ds::passwords[8],"ilovekalilinux");
    strcpy(ds::passwords[9],"agent47");



}
