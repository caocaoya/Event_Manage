
/*****************************************************************
	*	文件名： 	task_run.c
	*
	*	作者： 		曹亚鹏
	*
	*	说明： 		该文件主要是APP层所有输出函数的集合。
	*
	*	修改记录：  20200919
    *                
****************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

Event_Manage_Type   Event_Mange;

/*******************************************************
  * 函数功能: 注册任务统计
  * 输入参数: 
  * 返 回 值: 无
  * 说    明：无
*******************************************************/
uint8_t Event_Register(char *name, Event_Manage_Type * event_manage, uint8_t *register_handle)
{
    uint8_t status = REGISTER_NULL;
    
    if(EVEN_MAX < event_manage -> Event_Tatol_Count)
    {
        Even_Log("EVEN_Register over!\n\n");
        status = REGISTER_OVER_MAX;
    }
    //字符串的名字太长啦！
    else if()
    {
       status = REGISTER_TOO_LONG; 
    }
    //名字已经注册
    else if()
    {
       status = REGISTER_SAME_NAME; 
    }
    //标志位已经设置
    else if()
    {
      status = REGISTER_ENABLE_BORE;  
    } 
    else
    {
        strcpy(name, event_manage -> Task_Param[event_manage -> Event_Tatol_Count].Task_Name);
        Enable_Register_Table(event_manage -> Event_Tatol_Count, event_manage -> Event_Register);
        register_handle = event_manage -> Event_Tatol_Count;
        event_manage -> Event_Tatol_Count ++;
        status = REGISTER_OK;
    }
    
    return status;
}


uint8_t Enable_Register_Table(uint8_t bit_number, uint32_t data)
{
    
}

uint8_t Disable_Register_Table(uint8_t bit_number, uint32_t data)
{
    
}

uint8_t Even_Run_Task(void)
{
    
}



















