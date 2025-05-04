#include "stm32h7xx_hal.h"

#include "main.h"

/* USER CODE BEGIN extern C prototypes */
extern "C" {
    extern DSI_HandleTypeDef hdsi;
    extern LTDC_HandleTypeDef hltdc;

    uint8_t pCols[4][4] =
    {
        {0x00, 0x00, 0x00, 0xC7}, /*   0 -> 199 */
        {0x00, 0xC8, 0x01, 0x8F}, /* 200 -> 399 */
        {0x01, 0x90, 0x02, 0x57}, /* 400 -> 599 */
        {0x02, 0x58, 0x03, 0x1F}, /* 600 -> 799 */
    };

    uint8_t pColLeft[] = { 0x00, 0x00, 0x01, 0x8f }; /*   0 -> 399 */
    uint8_t pColRight[] = { 0x01, 0x90, 0x03, 0x1F }; /* 400 -> 799 */

    /* Request tear interrupt at specific scanline. Implemented in BoardConfiguration.cpp */
    void LCD_ReqTear();

    /* Configures display to update indicated region of the screen (200pixel wide chunks) - 16bpp mode */
    void LCD_SetUpdateRegion(int idx);

    /* Configures display to update left half of the screen. Implemented in BoardConfiguration.cpp  - 24bpp mode*/
    void LCD_SetUpdateRegionLeft();

    /* Configures display to update right half of the screen. Implemented in BoardConfiguration.cpp - 24bpp mode*/
    void LCD_SetUpdateRegionRight();
}
/* USER CODE END extern C prototypes */

/* USER CODE BEGIN extern C functions */
extern "C" {

    /**************************** LINK OTM8009A (Display driver) ******************/
    /**
      * @brief  DCS or Generic short/long write command
      * @param  ChannelNbr Virtual channel ID
      * @param  Reg Register to be written
      * @param  pData pointer to a buffer of data to be write
      * @param  Size To precise command to be used (short or long)
      * @retval BSP status
      */
    int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t* pData, uint16_t Size)
    {
        int32_t ret = BSP_ERROR_NONE;

        if (Size <= 1U)
        {
            if (HAL_DSI_ShortWrite(&hdsi, ChannelNbr, DSI_DCS_SHORT_PKT_WRITE_P1, Reg, (uint32_t)pData[Size]) != HAL_OK)
            {
                ret = BSP_ERROR_BUS_FAILURE;
            }
        }
        else
        {
            if (HAL_DSI_LongWrite(&hdsi, ChannelNbr, DSI_DCS_LONG_PKT_WRITE, Size, (uint32_t)Reg, pData) != HAL_OK)
            {
                ret = BSP_ERROR_BUS_FAILURE;
            }
        }

        return ret;
    }

    /**
      * @brief  DCS or Generic read command
      * @param  ChannelNbr Virtual channel ID
      * @param  Reg Register to be read
      * @param  pData pointer to a buffer to store the payload of a read back operation.
      * @param  Size  Data size to be read (in byte).
      * @retval BSP status
      */
    int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t* pData, uint16_t Size)
    {
        int32_t ret = BSP_ERROR_NONE;

        if (HAL_DSI_Read(&hdsi, ChannelNbr, pData, Size, DSI_DCS_SHORT_PKT_READ, Reg, pData) != HAL_OK)
        {
            ret = BSP_ERROR_BUS_FAILURE;
        }

        return ret;
    }
}
