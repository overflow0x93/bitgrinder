//
// Created by overflow on 2/12/18.
//

#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

#ifndef BITGRINDER_SYSTATUS_H
#define BITGRINDER_SYSTATUS_H

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

int statusmsg(const char* line, const char* status, int color=1);

#endif //BITGRINDER_SYSTATUS_H