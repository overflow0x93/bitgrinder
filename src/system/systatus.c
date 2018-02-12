//
// Created by overflow on 2/12/18.
//

#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

struct stat info;

/*
void incspin()
{
    // \|-/|
}

bool direxist(const char* pathname)
{

    if( stat( pathname, &info ) != 0 )
        return false;
        //printf( "cannot access %s\n", pathname );
    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
        return true;
        //printf( "%s is a directory\n", pathname );
    else
        return false;
    //printf( "%s is no directory\n", pathname );

}
*/

int msglen(const char * msg)
{
    int len=0;
    while (msg[len] != 0x00)
    {
        len++;
    }
    return len;
}

int statusmsg(const char* line, const char* status, int color=1)
{
    printf(KWHT,"");
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    int cwidth=ws.ws_col;
    int remaining = cwidth-msglen(line)-12;
    std::cout<<line;
    int i=0;
    for(;i<remaining;i++) printf(" ");
    std::cout<<"[ ";
    i=0;
    for(;i<((8-msglen(status))/2);i++) printf(" ");
    if (color==1)printf(KWHT,status);
    else if (color==2)printf(KGRN,status);
    else if (color==3)printf(KRED,status);
    else if (color==4)printf(KYEL,status);
    else if (color==5)printf(KCYN,status);
    else printf(KWHT,status);
    std::cout<<status;
    // 12 char msg status block i.e. [   FAIL   ]
    printf(KWHT,"");
    i=0;
    for(;i<((8-msglen(status))/2);i++) printf(" ");
    std::cout<<" ]\r\n";

    return 0;
}

/*
int main(int argc, char *argv[])
{

    statusmsg("Status","Fail", 3);
    statusmsg("Random Garbage...","GIGO",5);
    statusmsg("Status","Derppy", 4);
    statusmsg("More Random","Fail", 3);
    statusmsg("1234","Fail", 3);
    statusmsg("Testing","Pass", 2);
    std::cout<<"/etc exists:    "<<direxist("/etc")<<"\r\n";
    std::cout<<"/Etc exists:    "<<direxist("/Etc")<<"\r\n";
    std::cout<<"./test exists:    "<<direxist("./test")<<"\r\n";
    std::cout<<"./.test exists:    "<<direxist("./.test")<<"\r\n";
    std::cout<<"~/.config exists:    "<<direxist("~/.config")<<"\r\n";
    return 0;
}
 */