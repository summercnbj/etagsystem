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
	printf("sourceLen = %d\n", sourceLen  );
#define BUFFER_LEN 4000
	Bytef dest[BUFFER_LEN];
	memset(dest,0,BUFFER_LEN);
	uLongf destLen = BUFFER_LEN;

	int c = Z_BUF_ERROR;
	c = compress (dest, &destLen,  source,  sourceLen);
	printf("compress = %d\n", c  );
	printf("destLen= %d\n", destLen );

    if ( c != Z_OK )
    {
         printf("\nzlib compress failed (c=%d).\n", c);
         err = 1;
    }

	Bytef dest1[BUFFER_LEN];
	memset(dest1,0,BUFFER_LEN);
	uLongf destLen1 = BUFFER_LEN;
	c = uncompress (dest1,   &destLen1, dest, destLen);
	printf("uncompress = %d\n", c  );
	printf("destLen1= %d\n", destLen1 );
	printf("dest1= %s\n", dest1 );

    if ( c != Z_OK )
    {
         printf("\nzlib uncompress failed (c=%d).\n", c);
         err = 1;
    }

    if ((sourceLen != destLen1) || memcmp(source, dest1, destLen1) )
    {
         printf("Compression and/or decompression failed!\n");
         printf("\tInput data length [sourceLen] : %d\n", sourceLen);
         printf("\tCompressed data length [destLen] : %d\n", destLen);
         printf("\tUncompressed data length [destLen1]: %d\n", destLen1);

        if ( memcmp(source, dest1, destLen1) )
        {
        	printf("\tpTestData and pUnCompBuf contain different data!\n");
        }
        else
        {
            printf("\ndest_len:%d\ndest_data:%s\nsrc_src:%s\n",destLen1,dest1,source);
        }

        err = 1;
    }
    else
    {
    	printf("\n[SUCCESSFUL]dest_len:%d\ndest_data:%s\nsrc_data:%s\n",destLen1,dest1,source);
    }

    return err;
}
