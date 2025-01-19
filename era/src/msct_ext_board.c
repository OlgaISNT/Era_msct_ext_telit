/*
 * msct_ext_board.c
 *
 *  Created on: Nov 11, 2024
 *      Author: olgas
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>

//#include <stdbool.h>
#include <inttypes.h>

#include "m2mb_types.h"
#include "m2mb_sys.h"
#include "m2mb_os_api.h"
#include "at_command.h"
#include "params.h"
#include "factory_param.h"
#include "sys_param.h"
#include "prop_manager.h"
#include "log.h"
#include "msct_ext_board.h"
#include "../utils/hdr/mcp2515.h"
#include "../utils/hdr/can_util.h"
//void can_cb(MESSAGE message);
 tcmd_msct_ext cmd_msct_ext;
 char  cmd_msct_ext_start[]= "$MSCT";

 uint32_t create_UserTxbuf_cmd(uint8_t *txbuf, uint32_t cmd , MESSAGE message);

 void msct_ext_board_msg_parse(char *data, UINT32 size) {

	   MESSAGE readMessage = {0};
       uint32_t uOffs = 0;
	//   StrToHex((uint8_t*)&data[5], size, &cmd_msct_ext.RxBuf[0]);
       memcpy(&cmd_msct_ext.RxBuf[0], &data[5], size);
	  // for (int i =0; i < 30 ; i++)

	//  LOG_DEBUG("Parse: %d %d %d %d\r\n", cmd_msct_ext.RxBuf[0] ,cmd_msct_ext.RxBuf[1], cmd_msct_ext.RxBuf[2], cmd_msct_ext.RxBuf[3] );


	   cmd_msct_ext.len = cmd_msct_ext.RxBuf[uOffs ];
	   uOffs +=1;
	   cmd_msct_ext.cmd_id = cmd_msct_ext.RxBuf[uOffs];
	    uOffs +=1;
	  // cmd_msct_ext.len = size;
	  // LOG_DEBUG("Parse: %d %d\r\n",cmd_msct_ext.cmd_id , cmd_msct_ext.len );
	   switch ( cmd_msct_ext.cmd_id) {

	         case CAN_msg:
	        readMessage.id = get_uint32( &cmd_msct_ext.RxBuf[uOffs] /*(const unsigned char*) (data +  uOffs + 5)*/ , 0);
	        uOffs += 4;
	        readMessage.EID8 = cmd_msct_ext.RxBuf[uOffs ];
	        uOffs += 1;

	        readMessage.EID0 = cmd_msct_ext.RxBuf[uOffs ];
	        uOffs += 1;
	        readMessage.DLC = cmd_msct_ext.RxBuf[uOffs ];
	        uOffs += 1;
	     //   LOG_DEBUG("CAN_CMD:%d %d %d",  readMessage.id ,  readMessage.DLC , cmd_msct_ext.cmd_id);//



	         memcpy(&readMessage.data[0], &cmd_msct_ext.RxBuf[uOffs], 8);
	     //   LOG_DEBUG("CAN_CMD:%d %d %d", readMessage.data[0] ,  readMessage.data[1] , readMessage.data[2]);//

	         can_cb(readMessage);
	       // 	 msct_ext_board_CAN_msg_parse(char *data, UINT32 size) ;
             break;

	         default:
	          break;

	   }



}





 uint32_t create_UserTxbuf_cmd(uint8_t *txbuf, uint32_t cmd , MESSAGE message)
 {
  uint32_t offset = 0;
 	  switch(cmd)
 	    {
 	    case CAN_msg:

 	    	*(txbuf + offset) = cmd;
 	    	offset += 1;
 	    	set_uint32((txbuf + offset), message.id, /*EGTS_B_ENDIAN*/0);
             offset += 4;
             *(txbuf + offset) = message.EID8;
             offset += 1;
             *(txbuf + offset) = message.EID0;
             offset += 1;
             *(txbuf + offset) = message.DLC;
             offset += 1;
        //     LOG_DEBUG("CAN_uart:%d %d %d", message.DLC, message.id , message.EID8);//
          //   memcpy(&cmd_msct_ext.TxBuf[uOffs], &cmd_msct_ext.tcan_cmd.header.DLC, 1);
             memcpy(txbuf + offset, &message.data[0], 8);
              offset += 8;


 	    	 break;

 	    	    default:
 	    	    break;
 	    	    }
 return offset;

 }



 uint32_t msct_ext_board_exec_cmd(uint32_t cmd ,  MESSAGE message)
{
	uint32_t uOffs = 0 ;
	uint8_t		uOffs_cmd =0;

	  memcpy(&cmd_msct_ext.UserTxBuf[0], &cmd_msct_ext_start ,  strlen(cmd_msct_ext_start));
	  uOffs += strlen(cmd_msct_ext_start);

    switch(cmd)
    {
    case CAN_msg:

       	uOffs_cmd += create_UserTxbuf_cmd(&cmd_msct_ext.TxBuf[0], cmd , message);

        memcpy(&cmd_msct_ext.UserTxBuf[uOffs] , &uOffs_cmd, 1);
        uOffs +=1;
     	memcpy(&cmd_msct_ext.UserTxBuf[uOffs] , &cmd_msct_ext.TxBuf[0], uOffs_cmd);
    	uOffs += uOffs_cmd;
    	// cmd_msct_ext.CRC16 =

    break;

    default:
    break;

	}
return uOffs;

	}


 const char Hex[]={"0123456789ABCDEF"};


 	void Hex_Str(uint8_t hex, uint8_t *str) {
 	    *str++ = Hex[hex >> 4];
 	    *str++ = Hex[hex & 0xF];
 	}

 	void set_uint32(unsigned char* lpDestBuf, const uint32_t ulVal, BOOLEAN endian)
 		{
 			if (endian) // big endian (The highest bit first)
 			{
 				*(lpDestBuf++) = (unsigned char)((ulVal >> 24) & 0xFF);
 				*(lpDestBuf++) = (unsigned char)((ulVal >> 16)& 0xFF);
 				*(lpDestBuf++) = (unsigned char)((ulVal >> 8) & 0xFF);
 				*(lpDestBuf++) = (unsigned char)(ulVal & 0xFF);
 			}
 			else            // litle endian (the lowest bit first)
 			{
 				*(lpDestBuf++) = (unsigned char)(ulVal & 0xFF);
 				*(lpDestBuf++)  = (unsigned char)((ulVal >> 8) & 0xFF);
 				*(lpDestBuf++)  = (unsigned char)((ulVal >> 16) & 0xFF);
 				*(lpDestBuf++) = (unsigned char)((ulVal >> 24) & 0xFF);
 			}
 		}

 	 uint32_t get_uint32( const unsigned char* lpBuf, _Bool endian)
 		{
 		uint32_t	ulVal = 0L;
 			if (endian) // big endian
 			{
 				ulVal |= *lpBuf;
 				ulVal <<= 8;
 				ulVal |= *(lpBuf + 1);
 				ulVal <<= 8;
 				ulVal |= *(lpBuf + 2);
 				ulVal <<= 8;
 				ulVal |= *(lpBuf + 3);
 			}
 			else            // litle endian
 			{
 				ulVal |= *(lpBuf + 3);
 				ulVal <<= 8;
 				ulVal |= *(lpBuf + 2);
 				ulVal <<= 8;
 				ulVal |= *(lpBuf + 1);
 				ulVal <<= 8;
 				ulVal |= *lpBuf;
 			}
 			return ulVal ;
 		}


 	 uint16_t get_uint16(void *lpBuf, _Bool endian) {
 	     uint8_t *pntr = lpBuf;
 	     uint16_t usVal = 0;

 	     if (endian) // big endian
 	     {
 	         usVal |= *pntr;
 	         usVal <<= 8;
 	         usVal |= *(pntr + 1);
 	     } else            // litle endian
 	     {
 	         usVal |= *(pntr + 1);
 	         usVal <<= 8;
 	         usVal |= *pntr;
 	     }
 	     return usVal;
 	 }

 	 void set_uint16(void* lpDestBuf, uint16_t usVal, _Bool endian) {
 	     uint8_t *pntr = lpDestBuf;
 	     if (endian) {
 	         *(pntr++) = (uint8_t) ((usVal >> 8) & 0xFF);
 	         *(pntr++) = (uint8_t) (usVal & 0xFF);
 	     } else {
 	         *(pntr++) = (uint8_t) (usVal & 0xFF);
 	         *(pntr++) = (uint8_t) ((usVal >> 8) & 0xFF);
 	     }
 	 }


 	/*------------------------------------------------------------------------------
 	 * �������������� ������ Buf �������� uVal � ����������������� ������������������
 	 * � ������ mess
 	 */
 	void StrToHex(uint8_t* Buf, uint32_t uVal, uint8_t * mess) {
 	    uint8_t cn1;
 	     uint32_t i;
 	    for (i = 0; i < uVal; i += 2) {
 	        if (Buf[i] < 0x41)
 	            cn1 = (Buf[i] - 0x30) << 4;

 	        else
 	            cn1 = (Buf[i] - 0x37) << 4;

 	        if (Buf[i + 1] < 0x41)
 	            *(mess++) = ((Buf[i + 1] - 0x30) & 0x0f) | (cn1 & 0xf0);

 	        else
 	            *(mess++) = ((Buf[i + 1] - 0x37) & 0x0f) | (cn1 & 0xf0);

 	    }

 	}


 	char *SearchStr(char *s1, int32_t l1, char *s2) {
 	     char chr1, chr2;
 	     uint32_t l2;

 	     if(l1 <= 0) return 0;
 	     l2 = strlen(s2);
 	     while (l1 > 0) {
 	         chr1 = (((*s1 >= 'A') && (*s1 <= 'Z')) ? (*s1 + ('a' - 'A')) : *s1);
 	         chr2 = (((*s2 >= 'A') && (*s2 <= 'Z')) ? (*s2 + ('a' - 'A')) : *s2);

 	         if (chr1 == chr2) {
 	             uint16_t cl2 = l2;
 	             char *cd2 = s2;
 	             while ((l1 > 0) && (cl2 > 0)) {
 	                 chr1 = (((*s1 >= 'A') && (*s1 <= 'Z')) ? (*s1 + ('a' - 'A')) : *s1);
 	                 chr2 = (((*cd2 >= 'A') && (*cd2 <= 'Z')) ? (*cd2 + ('a' - 'A')) : *cd2);
 	                 if (chr1 != chr2) break;
 	                 ++s1;
 	                 --l1;
 	                 ++cd2;
 	                 --cl2;
 	             }
 	             if (!cl2) return (s1 - l2);
 	         } else {
 	             ++s1;
 	             --l1;
 	         }
 	     }
 	     return (0);
 	 }



