

#ifndef __TASEK_RUN_H
#define __TASEK_RUN_H

#define ENABLE_LOG         1
#define EVENT_MAX          32

#define EVENT_NAME_LENMAX  30

#define uint8_t  unsigned char 
#define uint16_t unsigned short
#define uint32_t unsigned int

#if ENABLE_LOG
#define Even_Log printf
// void Even_Log(char *str)
// {
    // printf("%s",str);
// }
#else
#define Even_Log printf
// void Even_Log(char *str)
// {
    
// }  
#endif

typedef struct enum
{
    EVENT_OK,
    EVENT_ERROR
}Status_Type;

typedef struct enum
{
    REGISTER_NULL,
    REGISTER_OK,
    REGISTER_TOO_LONG,
    REGISTER_SAME_NAME,
    REGISTER_OVER_MAX
}Register_Status_Type;


typedef struct 
{
   char      Task_Name[EVENT_NAME_LENMAX];   //任务运行的名字。
   uint32_t  Task_Run_Count;  //运行的次数。
   
}Task_Param_Type;

typedef struct 
{
    uint32_t          Task_All_Tatol;
    Task_Param_Type   Task_Param_Status[EVENT_MAX];
}Manage_Param_Type;

   
typedef struct 
{
    uint8_t           Event_Tatol_Count; //注册的任务的总数。
    uint32_t          Event_Register;    //任务注册登记表。
    uint32_t          Event_Run_Status;  //已注册的任务运行状态。

    Manage_Param_Type Task_Param;       //注册的任务的运行状态。
}Event_Manage_Type;


uint8_t Event_Register(char *name, Event_Manage_Type * event_manage, uint8_t *register_handle);
uint8_t Event_Unregister(Event_Manage_Type * event_manage, uint8_t register_handle);
uint8_t Enable_Register_Table(uint8_t bit_number, uint32_t *data);
uint8_t Disable_Register_Table(uint8_t bit_number, uint32_t *data);
uint8_t Get_Bit_Status(uint32_t *bit_data, uint8_t bit_number);
uint8_t Event_Task_Statistic(Event_Manage_Type * event_manage, uint8_t register_handle);
uint8_t Even_Run_Task(uint8_t register_handle);
uint8_t Event_Trig(Event_Manage_Type * event_manage);


#endif











