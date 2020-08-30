#ifndef __EXFUNS_H
#define __EXFUNS_H 					   
#include <stm32f10x.h>
#include "ff.h"


u8 mf_scan_files(u8 * path);
FRESULT exf_getfree(char *drv, int *total, int *free);
#endif


