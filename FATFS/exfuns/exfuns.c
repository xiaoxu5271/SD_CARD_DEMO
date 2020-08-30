#include "string.h"
#include "exfuns.h"
#include "usart.h"

FRESULT exf_getfree(char *drv, int *total, int *free)
{
	FATFS *fs1;
	FRESULT res;
  int fre_clust=0, fre_sect=0, tot_sect=0;

	res = f_getfree((const TCHAR*)drv, (DWORD*)&fre_clust, &fs1);
	if(res == 0)
	{
		tot_sect = (fs1->n_fatent - 2) * fs1->csize;	
		fre_sect = fre_clust * fs1->csize;			
#if _MAX_SS != 512				  				
		tot_sect *= fs1->ssize / 512;
		fre_sect *= fs1->ssize / 512;
#endif
		*total = tot_sect >> 1;	
		*free = fre_sect >> 1;	
	}
	return res;
}

FILINFO fileinfo;
DIR dir;
u8 mf_scan_files(u8 * path)
{
	FRESULT res;
    char *fn;   /* This function is assuming non-Unicode cfg. */

    res = f_opendir(&dir,(const TCHAR*)path); //打开一个目录
    if(res == FR_OK)
	{
		while(1)
		{
		    res = f_readdir(&dir, &fileinfo);
			if (res != FR_OK || fileinfo.fname[0] == 0)
			{
				break;
			}
			fn = fileinfo.fname;
			printf("%s/", path);//打印路径
			printf("%s\r\n",fn);//打印文件名
		}
	}
    return res;
}








