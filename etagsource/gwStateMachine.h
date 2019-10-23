/*
 * sm.h
 * statemachine constants
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef GWSTATEMACHINE_H_
#define GWSTATEMACHINE_H_


#define GW_State_Illegal 0xff  //非法：数据库里没有该mac。
//未初始化，未绑定有1种:
#define GW_State_Initial_NotLocated 0x01//未初始化： 数据库里有该mac，未被设置门店, 网关flash里无CLOUD_INFO和short PW。

//已初始化，未绑定
#define GW_State_Offline_NotLocated 0x02//有3种(都是不在线；若在线会被自动置为GW_State_Initial_NotLocated)：
#define GW_State_NeverOnline_NotLocated 0x21//该网关有初始化GW_CONFIG(未知正确性)但是从未发过心跳包，未绑定门店。
#define GW_State_Offline_ShortPWmodified_NotLocated 0x22//该网关有初始化正确的GW_CONFIG且发过心跳包，未绑定门店。
#define GW_State_Offline_ShortPWok_NotLocated 0x23//该网关有初始化正确的GW_CONFIG且发过心跳包，未绑定门店

//未初始化，已绑定有1种： (云服务器里有appXXX配置数据，但是可能被按键复位了，不用编程，会被云服务器诊断为GW_State_Offline_Located)
#define GW_State_Initial_Located 0x03// 未初始化已经绑定门店。

//已初始化，已绑定在线有1种：
#define GW_State_Online_Located 0x04//：最近一次心跳包在GW_OffPeriod_MAX之内。

//已初始化，已绑定不在线
#define GW_State_Offline_Located 0x05//有3种：
#define GW_State_NeverOnline_Located 0x51//该网关有初始化GW_CONFIG(未知正确性)但是从未发过心跳包，已绑定门店。
#define GW_State_Offline_ShortPWok_Located 0x52//该网关有初始化GW_CONFIG(正确曾经发过)但是最近未发心跳包，已绑定门店;lastHB之后没有修改两次或以上密码。
#define GW_State_Offline_ShortPWmodified_Located 0x53//该网关有初始化GW_CONFIG(正确曾经发过)但是最近未发心跳包，已绑定门店，已绑定门店;lastHB之后有修改两次或以上密码。



//泛状态
#define GW_State_Offline 0xfe//  包含已初始化，未绑定GW_State_Offline_NotLocated =0x02有3种和已初始化，已绑定不在线GW_State_Offline_Located =0x05有3种。

//不在线：最近一次心跳包(网关或价签心跳包都算)在GW_OffPeriod_MAX外。其中GW_OffPeriod_MAX = GW_INTERVAL_at_HALFMINUTE*GW_RETURN_RATIO之外(可能没有网络，可能云的shortPW密码改了，可能自身故障) 。 GW_RETURN_RATIO暂定为10
#define GW_INTERVAL_at_HALFMINUTE 20//10分钟
#define GW_RETURN_RATIO 10
#define GW_OffPeriod_MAX (GW_INTERVAL_at_HALFMINUTE*GW_RETURN_RATIO)

//专门用来排障的状态
#define GW_State_Online_Error_Located 0xfd// 如果某一个routerMac下有网关捆绑了多个店，则这些网关的shop RED led都快闪，提示要检查其中某些网关捆绑错了门店。







#endif /* GWSTATEMACHINE_H_ */
