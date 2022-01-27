#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>
#include<driver/gpio.h>


QueueHandle_t sensor_que;

// . Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. 
// Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.

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

   while(1){
  printf("TAsk3"); 
  vTaskDelay(3000/portTICK_PERIOD_MS);
   }
}


void task4(void *pv)
 {
   int sensor_data =0;
   while(1){
     sensor_data++;
  printf("sensor task:%d\n",sensor_data); 
  xQueueSend(sensor_que,&sensor_data, portMAX_DELAY); 
  vTaskDelay(1000/portTICK_PERIOD_MS);
   }
}

void task5(void *pv)
 {
   int recieved_data;
  xQueueReceive(sensor_que,&recieved_data,portMAX_DELAY);
   printf("data is:%d\n",recieved_data); 
   vTaskDelay(1000/portTICK_PERIOD_MS);
} 

int app_main()
{

  BaseType_t result;
  TaskHandle_t xHandle,xHandle2,xHandle1,xHandle3,xHandle4;

    sensor_que = xQueueCreate(10,sizeof(int));
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
    result = xTaskCreate(task4,"task4",2048,NULL,8,&xHandle3);
      if(result==pdPASS){
      printf("TAsk4 created");
    }
    result = xTaskCreate(task5,"task5",2048,NULL,9,&xHandle4);
      if(result==pdPASS){
      printf("TAsk5 created");
    }

      return 0;
}

// run 'idf.py -p (PORT) flash'