

#include "gwBleParseUart.h"

#include "gwBleScanAndConnect.h"



//~~~~~~~~~~~~~~~~~见十一~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//正常的master scan都是在做处理peripheral HB;这里切换到send_newShortPW


void TIMER_TIMEOUT_NVRAM_DELETE_NEW_SHORTPW()
{

	//删除NVRAM ID NEW_SHORTPW
	deleteNvramId(NVRAMID_NEW_SHORTPW);

	//切换回去
	set_bleScan_type(BLESCAN_TYPE_HB);
}

void to_send_NEW_SHORTPW_ONBLE(uint8* shortPW)
{
	//TODO start timer TIMER_TIMEOUT_NVRAM_DELETE_NEW_SHORTPW
	//timeout: PERIOD_for_FIND_NO_ETAG_min * 60 seconds

	//正常的master scan都是在做处理peripheral HB;这里切换到send_newShortPW
	set_bleScan_type(BLESCAN_TYPE_SENDNEWSHORTPW);
}

//开机即检查：如果NVRAM添加ID NEW_SHORTPW存在
void onBoot_check_NEW_SHORTPW(uint8* shortPW)
{

	// 如果NVRAM ID NEW_SHORTPW存在，to_send_NEW_SHORTPW_ONBLE(shortPW);
	uint16 length =0;
	uint8* NEW_SHORTPW = readNvramId(NVRAMID_NEW_SHORTPW,&length);

	if(NEW_SHORTPW !=NULL)
	{
		to_send_NEW_SHORTPW_ONBLE(shortPW);
	}
}


void parseUartPackage(uint8* package,uint16 package_length)
{
	myPrintf("parseUartPackage package_length= %d\n",package_length);
	if(NULL == package || package_length < CMD_LENGTH)
	{
		return ;
	}

	switch(*package)
	{
	case CMD_GW_HB_FEEDBACK:
	{

	}
		break;
	case CMD_GW_NEW_SHORTPW:
	{
		if(package_length - CMD_LENGTH < SHORTPW_LENGTH)
		{
			return;
		}
		uint8* newShortPW = package + CMD_LENGTH;

		//先保存shortPW到NVRAM ID NEW_SHORTPW
		saveNvramId(NVRAMID_NEW_SHORTPW,newShortPW,SHORTPW_LENGTH);

		//发送newShortPW给价签
		to_send_NEW_SHORTPW_ONBLE(newShortPW);
	}
		break;


	default :
		break;
	}

}

