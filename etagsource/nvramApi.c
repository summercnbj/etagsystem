/*
 * nvramApi.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */


#include "nvramApi.h"
#include "itrackerCharArray.h"


//读ID。长度存入data_length
uint8* readNvramId(uint16 id, uint16* data_length)
{

	//TODO 读出NVRAM ID字节串，总长度写入地址data_length；若不存在，返回NULL


	return NULL;
}

//删除ID
itr_bool deleteNvramId(uint16 id)
{

	//TODO 删除NVRAM ID字节串，返回成功1或者失败0


	return itr_false;
}




itr_bool appendNvramId(uint16 id, uint8* data, uint16 data_length)
{
	//TODO 不论如何，在最后添加一个指定的NVRAM ID

	return itr_false;
}

//添加或修改ID
itr_bool saveNvramId(uint16 id, uint8* data, uint16 data_length)
{
	uint16 saved_data_length =0;
	uint8* find = readNvramId(id, &saved_data_length);
	if(find)
	{//已经存在

		uint8 compare = chararrayCompare( data, data_length, find, saved_data_length,0);
		if( 0 == compare)
		{//如果值没变,直接返回
			return itr_true;;
		}

		//和已经存在的ID内容不同，删除NVRAM ID
		itr_bool delete = itr_false;
		while(!delete)
		{
			delete = deleteNvramId(id);
		}
	}
	itr_bool append = appendNvramId(id, data, data_length );

	return append;
}





