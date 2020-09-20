

#ifndef __TASEK_RUN_H
#define __TASEK_RUN_H


#define EVEN_MAX    32
#define ENABLE_LOG  1


#if ENABLE_LOG
void Even_Log(char *str)
{
    printf("%s",str);
}
#else
void Even_Log(char *str)
{
    
}  
#endif

struct enum
{
    EVENT_OK,
    EVENT_ERROR
}Status_Type;

struct enum
{
    REGISTER_NULL,
    REGISTER_OK,
    REGISTER_TOO_LONG,
    REGISTER_SAME_NAME,
    REGISTER_ENABLE_BORE,
    REGISTER_OVER_MAX
}Register_Status_Type;

struct 
{
   char      Task_Name[30];   //任务运行的名字。
   uint32_t  Task_Run_Count;  //运行的次数。
   
}Manage_Param_Type;

struct 
{
    uint8_t           Event_Tatol_Count; //注册的任务的总数。
    uint32_t          Event_Register;    //任务注册登记表。
    uint32_t          Event_Run_Status;  //已注册的任务运行状态。
    uint32_t          Task_All_Tatol;
    Manage_Param_Type Task_Param[EVEN_MAX];       //注册的任务的运行状态。
}Event_Manage_Type;




#endif

