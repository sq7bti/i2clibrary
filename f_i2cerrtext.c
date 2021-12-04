
/****** i2c.library/I2CErrText **********************************************
*
* NAME
*   I2CErrText -- returns text description of an error code (V39)
*
* SYNOPSIS
*   text = I2CErrText(errnum)
*                     D0
*
*   STRPTR I2CErrText(ULONG errnum);
*
* FUNCTION
*
* INPUTS
*
* RESULT
*
* SEE ALSO
*
*****************************************************************************
*
*/

#include "library.h"

#include <libraries/i2c.h>

#include <stdio.h>
#include <stdlib.h>

#include <proto/exec.h>
#include <proto/utility.h>
//#include <proto/dos.h>

__saveds STRPTR LibI2CErrText(struct MyLibBase *base __asm("a6"),
	ULONG errnum __asm("d0"))
{

	//RESULT_OK=0,        /* Last send/receive was OK */
	//RESULT_REJECT=1,       /* Data not acknowledged (i.e. unwanted) */
	//RESULT_NO_REPLY=2,      /* Chip address apparently invalid */
	//RESULT_SDA_TRASHED=3,
	//RESULT_SDA_LO=4,   /* SDA always LO \_wrong interface attached, */
	//RESULT_SDA_HI=5,
	//RESULT_SCL_TIMEOUT=6,
	//RESULT_SCL_HI=7,
	//RESULT_HARDW_BUSY=8

	switch((errnum >> 8) & 0xff) {
		case 1: //I2C_REJECT:
			return (STRPTR)"Error code 1: I2C_REJECT; Data not acknowledged (i.e. unwanted)";
			break;
		case 2: //I2C_NO_REPLY:
			return (STRPTR)"Error code 2: I2C_NO_REPLY; Chip address apparently invalid";
		break;
		case 3: //SDA_TRASHED:
			return (STRPTR)"Error code 3: SDA_TRASHED; SDA line randomly trashed. Timing problem?";
		break;
		case 4: //SDA_LO:
			return (STRPTR)"Error code 4: SDA_LO; SDA always LO. Wrong interface attached?";
		break;
		case 5: //SDA_HI:
			return (STRPTR)"Error code 5: SDA_HI; SDA always HI or none at all?";
		break;
		case 6: //SCL_TIMEOUT;
			return (STRPTR)"Error code 6: SCL_TIMEOUT; Might make sense for interfaces that can";
		break;
		case 7: //SCL_HI:
			return (STRPTR)"Error code 7: SCL_HI; read the clock line, but currently none can.";
		break;
		case 8: //I2C_HARDW_BUSY:
     	return (STRPTR)"Error code 8: I2C_HARDW_BUSY; Hardware allocation failed";
		break;
//		default:
//			return "Error unknown.";
//		break;
	}
//	return "Not supported";
	STRPTR stringpointer;

//	stringpointer = NULL;
	stringpointer = (STRPTR)AllocVec(256, 0);

//	strcpy(stringpointer, "Error code 0x");

	sprintf((char *)stringpointer, "ErrorCode 0x%08lu", errnum);

	return stringpointer;
}
