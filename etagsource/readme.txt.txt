一，看文件名：
哪个文件归属谁，看文件名字就知道。从文件名字上看不出归属的，就是公共文件。
etagBle开头的全是价签蓝牙上的文件。
gwBle开头的全是网关蓝牙上的文件。
gwWifi开头的全是网关上的文件。
serverXXX开头的全是服务器上的文件。

带有parse字样的一定是接收端。要解析收到的数据。
Hb是心跳包  Heart Beating
EncDec是压缩解压  Encode, Decode
StateMachine是状态机
BleAdv是蓝牙广播
BleScan是蓝牙扫描
testXXX是测试文件。

commands.h是所有的指令和常量。


二，
commands.h里：
#define TESTING_SUMMER  1//是个测试宏，跳过云，uart，ble将收发数据连接起来测试。



