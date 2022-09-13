#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "../data/data.h"

int write_message(const char* mes, int status);
int read_message(package** pack);

#endif