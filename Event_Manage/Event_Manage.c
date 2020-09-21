
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
#include "Event_Manage.h"

Event_Manage_Type   Event_Mange;


int  main()
{
	uint8_t task1_handle = 0;
	uint8_t task2_handle = 0;
	uint8_t task3_handle = 0;
	uint8_t task4_handle = 0;
	uint8_t task5_handle = 0;
	
	Event_Register("task1", &Event_Mange, &task1_handle);
	Event_Register("task2", &Event_Mange, &task2_handle);
	Event_Register("task3", &Event_Mange, &task3_handle);
	Event_Register("task4", &Event_Mange, &task4_handle);
	Event_Register("task5", &Event_Mange, &task5_handle);
	
	Even_Log("Event_Mange.Event_Register = %x,   Event_Mange.Event_Tatol_Count = %d \n\n", Event_Mange.Event_Register, Event_Mange.Event_Tatol_Count);
	
	Event_Run_Task(&Event_Mange, task1_handle);
	Event_Run_Task(&Event_Mange, task2_handle);
	Event_Run_Task(&Event_Mange, task3_handle);
	Event_Run_Task(&Event_Mange, task4_handle);
	//Event_Run_Task(&Event_Mange, task5_handle);


    //Event_Unregister(&Event_Mange, task1_handle);
	//Event_Unregister(&Event_Mange, task2_handle);
	//Event_Unregister(&Event_Mange, task3_handle);
	//Event_Unregister(&Event_Mange, task4_handle);
	//Event_Unregister(&Event_Mange, task5_handle);
	
	
	Event_Trig(&Event_Mange);	
	
	return 1;
}
/*******************************************************
  * 函数功能: 注册任务统计
  * 输入参数: 
  * 返 回 值: 无
  * 说    明：无
*******************************************************/
uint8_t Event_Register(char *name, Event_Manage_Type * event_manage, uint8_t *register_handle)
{
    uint8_t status = REGISTER_NULL;
    uint8_t count  = 0;
    uint8_t flag_same_name = 0;
    uint8_t flag_enable = 0, number_count = 0;
    
    if(EVENT_MAX < event_manage -> Event_Tatol_Count)
    {
        Even_Log("EVEN_Register over!\n\n");
        status = REGISTER_OVER_MAX;
    }
    //字符串的名字太长啦！
    else if(strlen(name) >  EVENT_NAME_LENMAX)
    {
       Even_Log("%s\n\n",name);
       status = REGISTER_TOO_LONG; 
    }
    else
    {
        for(count = 0;count < (event_manage -> Event_Tatol_Count); count ++)
        {
            //检测名字是否重复
           if( strstr(name, (event_manage -> Task_Param.Task_Param_Status[count].Task_Name) ))
           {
               flag_same_name = 1;
               break;
           }  
           //标志位是空的！
           if( !(flag_enable)  &&  !(Get_Bit_Status(&(event_manage -> Event_Register),count) )   && 
		       ((event_manage -> Event_Tatol_Count) < EVENT_MAX)  &&  
			   (Get_Bit_Status(&(event_manage -> Event_Register),EVENT_MAX)) )
           {
               number_count = count;
               flag_enable = 1;
           }               
        }

        //名字已经注册
        if( flag_same_name )
        {
           Even_Log("%d name(%s) is register\n\n", count, name);
           status = REGISTER_SAME_NAME; 
        }
        else
        {
            
            if(flag_enable)
            {
                strcpy( event_manage -> Task_Param.Task_Param_Status[number_count].Task_Name, name);
            
                Enable_Register_Table(number_count, &(event_manage -> Event_Register));
                
                *register_handle = number_count;
                Even_Log("%d register ok1 \n\n",*register_handle);
            }
            else
            {
                strcpy(event_manage -> Task_Param.Task_Param_Status[event_manage -> Event_Tatol_Count].Task_Name, name);
            
                Enable_Register_Table(event_manage -> Event_Tatol_Count, &(event_manage -> Event_Register));

                *register_handle = event_manage -> Event_Tatol_Count;  
                Even_Log("%d register ok \n\n",*register_handle);
            }

            event_manage -> Event_Tatol_Count ++;
            //event_manage -> Task_All_Tatol = event_manage -> Event_Tatol_Count;
            status = REGISTER_OK;   
        }
    }
    
    return status;
}
/*******************************************************
  * 函数功能: 注销任务统计
  * 输入参数: 
  * 返 回 值: 无
  * 说    明：无
*******************************************************/
uint8_t Event_Unregister(Event_Manage_Type * event_manage, uint8_t register_handle)
{
    uint8_t status = 0;
    
    if( !Get_Bit_Status(&(event_manage -> Event_Register), register_handle) )
    {
        strset( event_manage -> Task_Param.Task_Param_Status[register_handle].Task_Name,0);
        Disable_Register_Table(register_handle, &(event_manage -> Event_Register));
        Disable_Register_Table(register_handle, &(event_manage -> Event_Run_Status));
        
        event_manage -> Event_Tatol_Count--;
        status = REGISTER_OK; 
        
        Even_Log("Event_Unregister %d is Unregister OK %x.\n",register_handle, event_manage -> Event_Register);
    }
    else
    {
        Even_Log("Event_Unregister %d is not Register %x .\n",register_handle, event_manage -> Event_Register);
    }
    


    return status;
}

uint8_t Enable_Register_Table(uint8_t bit_number, uint32_t *data)
{
    uint32_t  enable_bit = 0x00000001;
    
    if(bit_number > EVENT_MAX)
    {
        Even_Log("bit_number error\n\n");
    }
    else
    {   
        {
            *data |= (enable_bit << bit_number);  
        }
        
    }
}

uint8_t Disable_Register_Table(uint8_t bit_number, uint32_t *data)
{
    uint32_t  clear_bit = 0x00000001;
    
    if(bit_number > EVENT_MAX)
    {
        Even_Log("bit_number error\n\n");
    }
    else
    {
        *data &= (~(clear_bit << bit_number)); 
    }    
}
uint8_t Get_Bit_Status(uint32_t *bit_data, uint8_t bit_number)
{
    uint8_t status = 1;
    
    uint32_t clear_bit = 0x00000001;
    uint32_t data = 0;
    
    data = (clear_bit << bit_number); 
    
	
	
    if( (*bit_data & data) )
    {
    //	Even_Log("Get_Bit_Status Enable   *bit_data = %x,   data = %d \n\n", *bit_data, data );
        status = 0;
    }
    else
    {
    //	Even_Log("Get_Bit_Status Disanble *bit_data = %x,   data = %d \n\n", *bit_data, data );
	}

    return status;
}

uint8_t Event_Task_Statistic(Event_Manage_Type * event_manage, uint8_t register_handle)
{
	//Even_Log("event_manage ->Event_Register = %x,   event_manage ->Event_Tatol_Count = %d,  register_handle = %d \n\n", event_manage ->Event_Register, event_manage ->Event_Tatol_Count, register_handle );
	
    if( !Get_Bit_Status(&(event_manage -> Event_Register), register_handle) )
    {
        event_manage -> Task_Param.Task_Param_Status[register_handle].Task_Run_Count++;
        Enable_Register_Table(register_handle, &(event_manage -> Event_Run_Status));
        Even_Log(" %d task run ok.\n",register_handle);
    }
    else
    {
        Even_Log("Event_Task_Statistic %d is not Register.\n",register_handle);
    }
    
}

uint8_t Event_Run_Task(Event_Manage_Type * event_manage, uint8_t register_handle)
{
    Event_Task_Statistic(event_manage, register_handle);
}

uint8_t Event_Trig(Event_Manage_Type * event_manage)
{
	uint8_t count = 0;
    uint32_t error_task_handle = 0;

    if( ((event_manage -> Event_Register) & (event_manage -> Event_Run_Status) == (event_manage -> Event_Register) ))
    {
    	Even_Log("Event_Trig is ok.\n",count);
        return 0;
    }
    else
    {
        error_task_handle = (event_manage -> Event_Register) ^ (event_manage -> Event_Run_Status);
        
        if(error_task_handle)
        {
	        for( count = 0; count < (event_manage -> Event_Tatol_Count); count++)
	        {
	           //打印出错误的任务
	           if(!Get_Bit_Status(&error_task_handle,count) )
	           {
	               Even_Log("Event_Trig %d is error.\n",count);
	           }               
	        }	
		}
		else
		{
			Even_Log("Event_Trig  event_manage ->Event_Tatol_Count = %d.\n",event_manage ->Event_Tatol_Count );
		}

    }

}

















