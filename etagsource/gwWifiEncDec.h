/*
 * gwEncDec.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWWIFIENCDEC_H_
#define GWWIFIENCDEC_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


/**
 * 给心跳包gwHbCore做blowfish加密
 * @shortPW 密码
 * @gwHbCore 心跳包
 * @gwHbCore_length 心跳包长度
 * @encryptedSize 密文长度存入该地址
 * @return 密文
 */
extern uint8* getHbCoreEncrypt(uint8* shortPW, uint8* hbCore ,uint16 hbCore_length, uint16 *encryptedSize);

extern uint8* formHbPackage(uint8* shortPW,  uint16 flowNo, uint8* gwMacBytes, uint8* hbCoreEncrypt ,uint16 hbCoreEncrypt_length, uint16 *package_length);

#endif /* GWWIFIENCDEC_H_ */
