#include "sys.h"
#include "delay.h"
#include "stmflash.h"
#include "IAP.h" 

iapfun jump2app; 
u32 iapbuf[512]; 	

/**
 *名称：iap_write_appbin
 *功能：将固件写入flash
 *输入：
	@appxaddr:APPflash起始地址
	@appbuf:接收二进制文件
	@appsize:一组数据大小
 *输出：
	@return 0：执行成功
			1:地址输入错误
			2:擦写扇区失败
			3:写入数据失败 
**/
int iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u32 t = 0,temp = 0,fwaddr=appxaddr;
	u16 i=0;
	u8 *dfu=appbuf,ret = 0;
	for(t=0;t<appsize;t+=4)
	{						   
		temp=(u32)dfu[3]<<24;   
		temp|=(u32)dfu[2]<<16;    
		temp|=(u32)dfu[1]<<8;
		temp|=(u32)dfu[0];	  
		dfu+=4;
		iapbuf[i++]=temp;	    
		if(i==512)
		{
			i=0; 
			ret = STMFLASH_Write(fwaddr,iapbuf,512);
			if(ret != 0)
				return ret;
			fwaddr+=2048;
		}
	} 
	if(i)
	{
		ret = STMFLASH_Write(fwaddr,iapbuf,i);
		if(ret != 0)
			return ret;
	}
	return 0;
}

/**
 *名称：iap_load_app
 *功能：跳转APP函数
 *输入：
	@appxaddr:app地址ַ
 *输出：
	@return 0：跳转失败，栈顶检查不存在
			1：跳转成功
**/
int iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶是否存在
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);			
		MSR_MSP(*(vu32*)appxaddr);			
		__set_PRIMASK(1);							//关闭总中断
		jump2app();									//成功跳转APP
		return 1;
	}
	else
		return 0;
}		 
