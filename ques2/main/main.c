#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>
#include<freertos/timers.h>


//  Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms.
//   Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.



TimerHandle_t motor_handle;

void task1(void *pv)
 {
   while(1){
  printf("TAsk1"); 
  vTaskDelay(1000/portTICK_PERIOD_MS);
   }
}
void task2(void *pv)
 {
   while(1){
  printf("TAsk2"); 
  vTaskDelay(2000/portTICK_PERIOD_MS);
   }
}
void task3(void *pv)
 {
   int count=0;

   while(1){
     count++;
  printf("TAsk3"); 
  vTaskDelay(5000/portTICK_PERIOD_MS);
  if(count == 2){
  xTimerStart(motor_handle,0);
  }
   }
}

void MoterOff(TimerHandle_t xtimer) 
{
  printf("Timer handler");
}
int app_main()
{

  BaseType_t result;
  TaskHandle_t xHandle,xHandle2,xHandle1;
    printf("Hello pthread\n");  
    result = xTaskCreate(task1,"task1",2048,NULL,5,&xHandle);  
      if(result==pdPASS){
      printf("TAsk1 created");
    }
    result = xTaskCreate(task2,"task2",2048,NULL,6,&xHandle1); 
      if(result==pdPASS){
      printf("TAsk2 created");
    }
    result = xTaskCreate(task3,"task3",2048,NULL,7,&xHandle2);  
      if(result==pdPASS){
      printf("TAsk3 created");
    }
    motor_handle = xTimerCreate("MotorOFF", pdMS_TO_TICKS(2000),false, NULL,MoterOff);


      return 0;
}

// run 'idf.py -p (PORT) flash'