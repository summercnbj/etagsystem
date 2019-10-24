/*
 * etagStateMachine.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef ETAGSTATEMACHINE_H_
#define ETAGSTATEMACHINE_H_




#define Etag_State_Illegal  0xff//非法：数据库里没有该mac

//未初始化，未绑定有1种:
#define Etag_State_Initial_ProductUnbound 0x01//未绑定： 数据库里有该mac, 但是无绑定商品信息，无图案信息

//已初始化，未绑定
#define Etag_State_Offline_ProductUnbound 0x02//有3种(都是不在线；若在线会被自动置为Etag_State_Initial_ProductUnbound):
#define Etag_State_NeverOnline_ProductUnbound 0x21
#define Etag_State_Offline_ShortPWmodified_ProductUnbound 0x22
#define Etag_State_Offline_ShortPWok_ProductUnbound 0x23

//未初始化，已绑定
#define Etag_State_Initial_ProductBound 0x03
//#define Etag_State_Initial_ProductBound_Pixeldata 0x31
//#define Etag_State_Initial_ProductBound_NoPixeldata 0x32//没有图案不允许绑定

//已初始化，已绑定且在线
#define Etag_State_Online_ProductBound 0x04//有2种:
#define Etag_State_Online_Normal_ProductBound 0x41//没有新图案。
#define Etag_State_Online_ProductBound_New_Pixeldata 0x42// 有了新图案
//#define Etag_State_Online_ProductBound_NoPixelData 0x43//绑定了商品，却没有点阵数据及其MD5_16。上位系统(中石化零售系统)故障。没有图案不允许绑定。

//已初始化，已绑定且不在线
#define Etag_State_Offline_ProductBound 0x05//有3种:
#define Etag_State_NeverOnline_ProductBound 0x51//, 0x52没有图案不允许绑定。
#define Etag_State_Offline_ShortPWmodified_ProductBound 0x53//, 0x54没有图案不允许绑定。
#define Etag_State_Offline_ShortPWok_ProductBound 0x55//,0x56没有图案不允许绑定。



//泛状态
#define Etag_State_Offline 0xfe//包含已初始化，未绑定Etag_State_Offline_ProductUnbound = 0x02有3种和已初始化，已绑定且不在线Etag_State_Offline_ProductBound =0x05有3种。



//不在线：有1个网关mac，且最近一次心跳包在TAG_OffPeriod_MAX外。其中TAG_OffPeriod_MAX = TAG_INTERVAL_at_HALFMINUTE*TAG_RETURN_RATIO之外(可能距离网关太远，可能云和网关的shortPW密码改了，可能自身故障)。 TAG_RETURN_RATIO暂定为10。
#define TAG_INTERVAL_at_HALFMINUTE 10//5分钟
#define TAG_RETURN_RATIO 10
#define TAG_OffPeriod_MAX (TAG_INTERVAL_at_HALFMINUTE*TAG_RETURN_RATIO)





#endif /* ETAGSTATEMACHINE_H_ */
