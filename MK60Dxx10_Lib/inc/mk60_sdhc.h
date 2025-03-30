#ifndef _MK60_SDHC_H_
#define _MK60_SDHC_H_
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:sdhc底层

//SD卡类型定义
#define SD_CARD_TYPE_NONE      (0)
#define SD_CARD_TYPE_UNKNOW    (1)
#define SD_CARD_TYPE_SD        (2)
#define SD_CARD_TYPE_SDHC      (3)
#define SD_CARD_TYPE_SDIO      (4)
#define SD_CARD_TYPE_SDCOMBO   (5)
#define SD_CARD_TYPE_SDHCCOMBO (6)
#define SD_CARD_TYPE_MMC       (7)
#define SD_CARD_CEATA          (8)   

//SD初始化结构体
typedef struct 
{
    uint32_t baudrate; //通信速度
}SD_InitTypeDef;

//SD卡命令结构
typedef struct 
{
  uint32_t COMMAND;           //命令定义
  uint32_t ARGUMENT;          //参数
  uint32_t BLOCKS;            //块数
  uint32_t BLOCKSIZE;         //块大小
  uint32_t RESPONSE[4];       //命令回应信息
}SD_CommandTypeDef;

//SD构件通讯错误代码
#define ESDHC_OK                             (0)
#define ESDHC_ERROR_INIT_FAILED              (1)
#define ESDHC_ERROR_COMMAND_FAILED           (2)
#define ESDHC_ERROR_COMMAND_TIMEOUT          (3)
#define ESDHC_ERROR_DATA_TRANSFER            (4)
#define ESDHC_ERROR_INVALID_BUS_WIDTH        (5)

uint8_t SD_Init(SD_InitTypeDef* SD_InitStruct);
uint32_t SD_GetSizeInMB(void);
uint8_t SD_ReadSingleBlock(uint32_t sector, uint8_t *buf);
uint8_t SD_WriteSingleBlock(uint32_t sector, const uint8_t *buf);
uint8_t SD_ReadMultiBlock(uint32_t sector, uint8_t *buf, uint16_t blockCnt);
uint8_t SD_WriteMultiBlock(uint32_t sector,const uint8_t *buf, uint16_t blockCnt);
uint32_t SD_QuickInit(uint32_t baudrate);
uint8_t SD_InitCard(void);
#endif
