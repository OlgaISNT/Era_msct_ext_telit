/**
 * @file auxiliary.c
 * @version 1.0.0
 * @date 05.05.2022
 * @author: DKozenkov from RMerdeev
 * @brief app description
 */

/* Include files ================================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "m2mb_types.h"
#include "m2mb_os_api.h"
#include "auxiliary.h"
#include "../hdr/sms_manager.h"
#include "azx_timer.h"
#include "atc_era.h"
#include "tasks.h"
#include "log.h"
/* Local defines ================================================================================*/
/* Local typedefs ===============================================================================*/
/* Local statics ================================================================================*/
static const UINT8 Crc8Table[256] = {
        0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97,
        0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
        0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4,
        0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
        0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11,
        0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
        0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52,
        0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
        0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA,
        0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
        0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9,
        0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
        0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C,
        0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
        0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F,
        0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
        0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED,
        0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
        0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE,
        0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
        0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B,
        0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
        0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28,
        0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
        0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0,
        0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
        0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93,
        0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
        0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56,
        0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
        0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15,
        0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC
};

static const UINT16 Crc16Table[256] = {
        0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
        0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
        0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
        0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
        0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
        0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
        0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
        0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
        0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
        0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
        0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
        0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
        0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
        0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
        0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
        0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
        0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
        0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
        0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
        0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
        0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
        0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
        0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
        0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
        0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
        0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
        0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
        0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
        0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
        0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
        0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
        0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};
static const char Int2Char[20] = {0x30,0,0x31,0,0x32,0,0x33,0,0x34,0,0x35,0,0x36,0,0x37,0,0x38,0,0x39,0};
/* Local function prototypes ====================================================================*/
/* Static functions =============================================================================*/
/* Global functions =============================================================================*/

/***************************************************************************/
/*  Function   : auxiliary_hex_to_char                                     */
/*-------------------------------------------------------------------------*/
/*  Contents   : Convert hex data to char                                  */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT16 auxiliary_hex_to_char ( UINT8 *buffer_in, UINT8 num, char *buffer_out, UINT32 b_out_size ) {
    static UINT8 temp;
    static UINT8 temp1;
    UINT8 res = 0;
    memset(buffer_out, 0, b_out_size);
    for ( UINT8 i=0; i<num; i++ ) {
        temp = *(buffer_in+i);

        temp1 = (temp >> 4) & 0x0F;

        if ( temp1 <= 9 ) *(buffer_out+i*2) = temp1 + 0x30;
        else *(buffer_out+i*2) = temp1 + 0x37;

        res++;

        temp1 = temp & 0x0F;

        if ( temp1 <= 9 ) *(buffer_out+i*2+1) = temp1 + 0x30;
        else *(buffer_out+i*2+1) = temp1 + 0x37;

        res++;
    }

    return res;
}

/***************************************************************************/
/*  Function   : auxiliary_char_to_hex                                     */
/*-------------------------------------------------------------------------*/
/*  Contents   : Convert char data to hex                                  */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_char_to_hex ( char *buffer_in, UINT16 num, UINT8 *buffer_out ) {
    UINT8 temp;
    UINT8 temp1;
    UINT8 i;

    if ( num%2 ) return 0;

    num /= 2;

    for ( i=0; i<num; i++ )
    {
        temp = *(buffer_in+i*2);

        if ( (temp >= 0x30) && (temp <= 0x39) ) temp1 = ((temp - 0x30) << 4) & 0xF0;
        else if ( (temp >= 0x41) && (temp <= 0x46) ) temp1 = ((temp - 0x37) << 4) & 0xF0;
        else return 0;

        temp = *(buffer_in+i*2+1);

        if ( (temp >= 0x30) && (temp <= 0x39) ) temp1 |= (temp - 0x30) & 0x0F;
        else if ( (temp >= 0x41) && (temp <= 0x46) ) temp1 |= (temp - 0x37) & 0x0F;
        else return 0;

        *(buffer_out+i) = temp1;
    }

    return i;
}

/***************************************************************************/
/*  Function   : auxiliary_write_u8                                        */
/*-------------------------------------------------------------------------*/
/*  Contents   : Add UINT8 data to buffer                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_write_u8 ( UINT8 *buff, UINT8 ind, UINT8 value ) {
    buff[ind] = value;
    return (ind + 1);
}



/***************************************************************************/
/*  Function   : auxiliary_write_u16                                       */
/*-------------------------------------------------------------------------*/
/*  Contents   : Add UINT16 data to buffer                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_write_u16 ( UINT8 *buff, UINT8 ind, UINT16 value ) {
    buff[ind]     = (UINT8)(value & 0x00FF);
    buff[ind + 1] = (UINT8)(value >> 8);
    return (ind + 2);
}



/***************************************************************************/
/*  Function   : auxiliary_write_u32                                       */
/*-------------------------------------------------------------------------*/
/*  Contents   : Add UINT32 data to buffer                                    */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_write_u32 ( UINT8 *buff, UINT8 ind, UINT32 value ) {
    buff[ind]     = (UINT8)(value & 0x000000FF);
    buff[ind + 1] = (UINT8)(value >> 8);
    buff[ind + 2] = (UINT8)(value >> 16);
    buff[ind + 3] = (UINT8)(value >> 24);
    return (ind + 4);
}



/***************************************************************************/
/*  Function   : auxiliary_read_u8                                         */
/*-------------------------------------------------------------------------*/
/*  Contents   : Extract UINT8 data from buffer                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_read_u8 ( UINT8 *buff, UINT8* ind ) {
    UINT8 value = buff[*ind];
    (*ind)++;
    return value;
}



/***************************************************************************/
/*  Function   : auxiliary_read_u16                                        */
/*-------------------------------------------------------------------------*/
/*  Contents   : Extract UINT16 data from buffer                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT16 auxiliary_read_u16 ( UINT8 *buff, UINT8* ind ) {
    UINT16 value = (UINT16)(buff[*ind+1]);
    value <<= 8;
    value |= (UINT16)(buff[*ind]);
    (*ind) += 2;
    return value;
}



/***************************************************************************/
/*  Function   : auxiliary_read_u32                                        */
/*-------------------------------------------------------------------------*/
/*  Contents   : Extract UINT32 data from buffer                              */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT32 auxiliary_read_u32 ( UINT8 *buff, UINT8* ind ) {
    UINT32 value = (UINT32)(buff[*ind+3]);
    value <<= 8;
    value |= (UINT32)(buff[*ind+2]);
    value <<= 8;
    value |= (UINT32)(buff[*ind+1]);
    value <<= 8;
    value |= (UINT32)(buff[*ind]);
    (*ind) += 4;
    return value;
}

/***************************************************************************/
/*  Function   : auxiliary_swap                                            */
/*-------------------------------------------------------------------------*/
/*  Contents   : Swap byte                                                 */
/*                                                                         */
/*-------------------------------------------------------------------------*/
/***************************************************************************/

UINT8 auxiliary_swap ( UINT8 val ) {
    return (val << 4) | (val >> 4);
}



void auxiliary_int_to_char ( UINT16 src, char* dst ) {
    *dst = 0;
    UINT8 dig;
    UINT16 div = 10000;
    UINT8 fl = 0;
    for ( UINT8 i=0; i<5; i++ )
    {
        dig = src/div;
        if ( fl || dig )
        {
            fl = 1;
            if ( dig<10 ) strcat(dst, (Int2Char+dig*2));
        }
        src -= div*dig;
        div = div/10;
    }
}



void auxiliary_swap_u8 ( UINT8* src, UINT8* dst )
{
    *src = *src ^ *dst;
    *dst = *src ^ *dst;
    *src = *src ^ *dst;
}

UINT8 auxiliary_crc8( UINT8 *pcBlock, UINT8 len ) {
    UINT8 crc = 0xFF;
    while (len--)
        crc = Crc8Table[crc ^ *pcBlock++];
    return crc;
}

UINT16 auxiliary_crc16( UINT8 *pcBlock, UINT8 len ) {
    UINT16 crc = 0xFFFF;
    while (len--)
        crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];
    return crc;
}
