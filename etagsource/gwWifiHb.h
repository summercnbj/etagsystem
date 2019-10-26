/*
 * gwWifi.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef GWWIFIHB_H_
#define GWWIFIHB_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "nvramApi.h"



/** 获得已经加密组装了流水号的GW心跳包，准备发送到云服务器
 * @shortPW 密码
 * @flowNo 云请求的流水号
 * @macBytes 长度为MAC_BYTE_LENGTH=6
 * @battPercentage  电量百分比
 * @rootMacBytes 长度为MAC_BYTE_LENGTH
 * @isBusy 暂不用，填0
 * @productModel 型号常量字符串
 * @softwareVersion 软件版本常量字符串
 * @hardwareVersion 硬件版本常量字符串
 * @package_length 保存最终的字节总数
 * @return 心跳包; 或者  内存分配失败返回NULL
 * 心跳包总长度为package_length。
 *
 */




#endif /* GWWIFIHB_H_ */
