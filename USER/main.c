#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sdio_sdcard.h"
#include "ff.h"
#include "exfuns.h"

FATFS fs;

static int init(void);
static int create_file_test(void);
static void write_sd_test(void);

int main(void)
{

	if (init() < 0)
	{
		printf("Init fail\n");
	}
	else
	{
		printf("Test SD Creat file and write\n");
		create_file_test();
		write_sd_test();
	}

	while (1)
	{
	}
}

static int init(void)
{
	int i = 0;
	SD_Error sd_statue = SD_OK;
	FRESULT fatfs_status = FR_OK;
	int sd_space_total, sd_space_free;

	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	debug_uart_init(115200);
	// uart2_init(115200);
	// uart3_init(115200);
	// init_led();

	// TIM5_Cap_Init(0xffff, 7200 - 1);
	// for (i = 0; i < 10; i++)
	// {
	// 	delay_ms(1000);
	// }

	if ((sd_statue = SD_Init()) == SD_OK)
	{
		printf("tf card ok!\r\n");
	}
	else
	{
		printf("tf card error, error code = %d\r\n", sd_statue);
		return -1;
	}

	if ((fatfs_status = f_mount(&fs, "0:", 1)) == FR_OK)
	{
		printf("fatfs mount ok!\r\n");
	}
	else
	{
		printf("fatfs mount error, error code = %d\r\n", fatfs_status);
		return -1;
	}

	if ((fatfs_status = exf_getfree((char *)"0:", &sd_space_total, &sd_space_free)) == FR_OK)
	{
		printf("tf_space_total = %d, tf_space_free = %d!\r\n", sd_space_total, sd_space_free);
	}
	else
	{
		printf("fatfs get free error, code = %d\r\n", fatfs_status);
		return -1;
	}
	return 0;
}

static char g_file_name[20] = {0};
static int create_file_test(void)
{
	int n_serial = 0;
	FIL fil;
	FRESULT temp = FR_OK;
	for (n_serial = 0; n_serial < 1000; n_serial++)
	{
		sprintf(g_file_name, "test-1.txt");
		temp = f_open(&fil, g_file_name, FA_READ);
		if (temp == FR_OK)
		{
			f_close(&fil);
			continue;
		}
		else if (temp == FR_NO_FILE)
		{
			f_open(&fil, g_file_name, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
			f_close(&fil);
			printf("create file = %s\r\n", g_file_name);
			return 0;
		}
	}
	return -1;
}

static char sd_w_buf[400];
static void write_sd_test(void)
{
	FIL fil;
	UINT bw;
	static int n_count = 0;
	memset(&sd_w_buf, 0, sizeof(sd_w_buf));

	f_open(&fil, g_file_name, FA_WRITE);
	sprintf(sd_w_buf, "123456780qwerty");

	f_write(&fil, sd_w_buf, strlen(sd_w_buf), &bw);
	f_close(&fil);
}
