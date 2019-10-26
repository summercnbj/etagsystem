/*
 * testzlibApi.c
 *
 *  Created on: 2019年10月16日
 *      Author: summer
 */


#include "testzlibApi.h"

/*
 * 测试zlib加密再解密是否还原。 实测例子压缩3.4倍。
 * 提示：COMPRESS_BUFFLEN，UNCOMPRESS_BUFFLEN都可以 >= sourceLen 即可
 */
int testzlib(const Bytef *source, uLong sourceLen)
{
	/*
	 * 测试成功。
	 * 只需要/lib/libz.a即可。 lib下其他库均可删去。
	 */
	int err =0;
	myPrintf("sourceLen = %d\n", sourceLen  );
#define BUFFER_LEN 4000
	Bytef dest[BUFFER_LEN];
	memset(dest,0,BUFFER_LEN);
	uLongf destLen = BUFFER_LEN;

	int c = Z_BUF_ERROR;
	c = compress (dest, &destLen,  source,  sourceLen);
	myPrintf("compress = %d\n", c  );
	myPrintf("destLen= %d\n", destLen );

    if ( c != Z_OK )
    {
         myPrintf("\nzlib compress failed (c=%d).\n", c);
         err = 1;
    }

	Bytef dest1[BUFFER_LEN];
	memset(dest1,0,BUFFER_LEN);
	uLongf destLen1 = BUFFER_LEN;
	c = uncompress (dest1,   &destLen1, dest, destLen);
	myPrintf("uncompress = %d\n", c  );
	myPrintf("destLen1= %d\n", destLen1 );
	myPrintf("dest1= %s\n", dest1 );

    if ( c != Z_OK )
    {
         myPrintf("\nzlib uncompress failed (c=%d).\n", c);
         err = 1;
    }

    if ((sourceLen != destLen1) || memcmp(source, dest1, destLen1) )
    {
         myPrintf("Compression and/or decompression failed!\n");
         myPrintf("\tInput data length [sourceLen] : %d\n", sourceLen);
         myPrintf("\tCompressed data length [destLen] : %d\n", destLen);
         myPrintf("\tUncompressed data length [destLen1]: %d\n", destLen1);

        if ( memcmp(source, dest1, destLen1) )
        {
        	myPrintf("\tpTestData and pUnCompBuf contain different data!\n");
        }
        else
        {
            myPrintf("\ndest_len:%d\ndest_data:%s\nsrc_src:%s\n",destLen1,dest1,source);
        }

        err = 1;
    }
    else
    {
    	myPrintf("\n[SUCCESSFUL]dest_len:%d\ndest_data:%s\nsrc_data:%s\n",destLen1,dest1,source);
    }

    return err;
}
