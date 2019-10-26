/*
 * testzlibApi.h
 *
 *  Created on: 2019年10月16日
 *      Author: summer
 */

#ifndef TESTZLIBAPI_H_
#define TESTZLIBAPI_H_
#include "include/zlib.h"
#include "itracker88Platform.h"


/*
 * 测试zlib加密再解密是否还原。 实测例子压缩3.4倍。
 * 提示：COMPRESS_BUFFLEN，UNCOMPRESS_BUFFLEN都可以 >= sourceLen 即可
 */
extern int testzlib(const Bytef *source, uLong sourceLen);

#endif /* TESTZLIBAPI_H_ */
