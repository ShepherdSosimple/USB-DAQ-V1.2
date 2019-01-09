
#ifndef _USBCARD_DLL_V12_
#define _USBCARD_DLL_V12_



#ifndef USBCARDV12
#define MYAPI __declspec(dllimport)
#pragma comment(lib,"USBDAQ_DLL_V12.lib")
//#pragma comment(lib,"USBDAQ_DLL_V12X64.lib")
#else
#define MYAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif


// *********** 设备打开函数，成功返回0 ***********
MYAPI	int __stdcall OpenUsbV12(void);

// *********** 设备关闭函数，成功返回0 ***********
MYAPI	int __stdcall CloseUsbV12(void);

// *********** USB设备重新挂载函数，成功返回0，然后需要重新打开设备 ***********
MYAPI	int __stdcall ResetUsbV12(void);

 
// *********** 获取设备数量函数，成功返回0 ***********
MYAPI	int __stdcall GetDeviceCountV12(void);

// *********** 切换设备函数，成功返回0 ***********
MYAPI	int __stdcall SetCurDeviceV12(int Devicenum);


//多板卡操作函数，主要用在板子自带拨码开关
// *********** 获取拨码开关码值，成功返回0 ***********
MYAPI	int __stdcall GetSwitchNumV12(void);

// *********** 按拨码开关值设定当前板卡，成功返回0 ***********
MYAPI	int __stdcall SetSwitchNumV12(int ID);


// *********** 单次获取AD采集结果，成功返回0 ***********
MYAPI	int __stdcall ADSingleV12(int ad_mod, int chan, int gain, float* adResult);


// *********** 单通道AD连续采集一段数据，成功返回0 ***********
MYAPI	int __stdcall ADContinuV12(int ad_mod, int chan, int gain, int Num_Sample, int Rate_Sample, float  *databuf);


// *********** 单通道AD多通道连续采集一段数据，成功返回0 ***********
MYAPI	int __stdcall MADContinuV12(int ad_mod, int chan_first, int chan_last, int gain, int Num_Sample, int Rate_Sample, float  *mad_data);


// ********************** 配置AD单通道采集并启动，成功返回0 **********************
MYAPI	int __stdcall ADContinuConfigV12(int ad_mod, int chan, int gain, int Rate_Sample);

// ********************** 配置AD多通道采集并启动，成功返回0 **********************
MYAPI	int __stdcall MADContinuConfigV12(int ad_mod, int chan_first, int chan_last, int gain, int Rate_Sample);

// ********************** 返回当前缓存数据量大小，USB未打开返回-1 **********************
MYAPI	int __stdcall GetAdBuffSizeV12(void);  //-1 --- erro  

// ********************** 读取AD采集缓存，成功返回0 **********************
MYAPI	int __stdcall ReadAdBuffV12(float* databuf, int num);

// ********************** AD连续采集停止，成功返回0 **********************
MYAPI	int __stdcall ADContinuStopV12(void);



// *********** DA通道单值输出，成功返回0 ***********
MYAPI	int __stdcall DASingleOutV12(int chan,int value);

// *********** DA通道扫描数据发送，成功返回0 ***********
MYAPI	int __stdcall DADataSendV12(int chan,int Num,int *databuf);

// *********** DA通道扫描输出设置，成功返回0 ***********
MYAPI	int __stdcall DAScanOutV12(int chan,int Freq,int scan_Num);

// *********** PWM输出设置，成功返回0 ***********
MYAPI	int __stdcall PWMOutSetV12(int chan,int Freq,float DutyCycle);
//2.0  与5.0不同

// *********** PWM输入设置，成功返回0 ***********
MYAPI	int __stdcall PWMInSetV12(int mod);

// *********** PWM输入结果获取，成功返回0 ***********
MYAPI	int __stdcall PWMInReadV12(float* Freq, int* DutyCycle);

// *********** 计数器输入设置，成功返回0 ***********
MYAPI	int __stdcall CountSetV12(int mod);

// *********** 计数器结果读取，成功返回0 ***********
MYAPI	int __stdcall CountReadV12(int* count);

// *********** 开关量输出设定，成功返回0 ***********
MYAPI	int __stdcall DoSetV12(unsigned char chan,unsigned char state);

// *********** 开关量输入获取，成功返回0 ***********
MYAPI	int __stdcall DiReadV12(unsigned char *value);

// *********** 获取设备ID号，成功返回0 ***********
MYAPI	unsigned int __stdcall GetCardIdV12(void);

#ifdef __cplusplus
}
#endif



#endif

/*  delphi


function   OpenUsbV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   CloseUsbV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   GetDeviceCountV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function  SetCurDeviceV12(Devicenum:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll';

function   ADSingleV12(admod:integer;chan:integer;gain:integer;adResult:psingle):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   ADContinuV12(admod:integer;chan:integer;gain:integer;Num_Sample:integer;  Rate_Sample:integer;databuf:psingle):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   MADContinuV12(admod:integer;chan_first:integer;chan_last:integer;gain:integer;Num_Sample:integer; Rate_Sample:integer; mad_data:psingle):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   ADContinuConfigV12(admod:integer;chan:integer;gain:integer; Rate_Sample:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   MADContinuConfigV12(admod:integer;chan_first:integer;chan_last:integer;gain:integer; Rate_Sample:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll';

function   GetAdBuffSizeV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   ReadAdBuffV12(adbuf:psingle;num:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   ADContinuStopV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll';


function   DASingleOutV12(chan:integer;value:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   DADataSendV12(chan:integer;Num:integer;databuf:pinteger):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   DAScanOutV12(chan:integer;Freq:integer;scan_Num:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   PWMOutSetV12(chan:integer;Freq:integer;DutyCycle:single):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   PWMInSetV12(mode:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   CountSetV12(mode:integer):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   PWMInReadV12(Freq:psingle;DutyCycle:pinteger):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;
function   CountReadV12(count:pinteger):integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;

function   DoSetV12(chan:Byte;state:Byte):integer;stdcall;external 'USBDAQ_DLL_V12.dll';
function   DiReadV12(inport:pByte):integer;stdcall;external 'USBDAQ_DLL_V12.dll';

function   GetCardIdV12:integer;stdcall;external 'USBDAQ_DLL_V12.dll' ;

*/

