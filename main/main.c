
#include "config.h"
#include "main.h"

const char *TAG = "MAIN";

/*******************************************************************************
 Programa principal
******************************************************************************/
volatile int samples[SAMPLES_SIZE];
volatile int n = 0;

data_t datos = {.active_button = 0, .active_led = 0, .adc=0};

void app_main(void)
{
  char buffer_time [80];
  char name_buffer [90];
  char adc_msg[50];
  int len_data = 0;
  //datos.active_button = 0;

  CRONO_sntpInit();
  IO_adcInit();
  IO_gpioInit();
  IO_pwmInit();
  CRONO_timerInit();
  SD_mount();
  WIFI_init();
  MQTT_init();

  MQTT_subscribe("test/button");
  
  CRONO_getTime(buffer_time,sizeof(buffer_time));
  sprintf(name_buffer,"%s.csv",buffer_time);
  printf("Nombre: %s\r\n",name_buffer);

  FILE * f = SD_open(name_buffer, "w");
  SD_printf(f, "ADC\n");

  datos.active_button = 0;
  CRONO_timerStart(20);

  while(datos.active_button ==0)
  {
    sprintf(adc_msg,"%d", datos.adc);
    MQTT_publish("test/adc",adc_msg);
    printf("Datos: %s\r\n",adc_msg); 
    printf("GRABANDO: %i muestras de %i\r\n", n, SAMPLES_SIZE);
    printf("Envio de data\r\n");
    if(n==SAMPLES_SIZE){
      datos.active_button = 1;
      printf("Desactiva data\r\n"); 
      CRONO_timerStop();
    }
    CRONO_delayMs(500);
  }
  printf("Termino tiempo\r\n");
  CRONO_timerStop();
  len_data = n;

  for(int i = 0; i< len_data;i++)
  {
    SD_printf(f, "%d\n", samples[i]);
  }
  
  SD_close(f);
  

  while(1)
  {
    
    // Loop
    IO_toggleLed();
    CRONO_delayMs(100);
    

  }
  SD_unmount();

}


/** PARTE 1**/
/***
 * //IO_adcInit();
  //int x;

  WHILE
  //x = IO_readAdc();
  //CRONO_delayMs(250);
  //printf("Sensor: %i\r\n",x);
*/

/** PARTE 2 **/
/**
 * volatile int samples[SAMPLES_SIZE];
volatile int n = 0;
 * 
 * IO_adcInit();
  IO_gpioInit();
  IO_pwmInit();
  CRONO_timerInit();

  CRONO_timerStart(10);
  while(n<SAMPLES_SIZE)
  {
    printf("GRABANDO: %i muestras de %i\r\n",n,SAMPLES_SIZE);
    CRONO_delayMs(500);
  }
  CRONO_timerStop();
  printf("GRABACION FINALIZADA \r\n");
  IO_monitorPause("Presione Enter para continuar...\r\n");

  printf("INICIANDO REPRODUCCIÓN\n");
  for(n=0;n<SAMPLES_SIZE;n++){
      IO_pwmSet(samples[n] / 4096.0 *100);
      IO_monitorGraph(samples[n]);
      CRONO_delayMs(100);
  }
  IO_pwmSet(0);
  printf("REPRODUCCIÓN FINALIZADA\n");
  n = 0;
 * 
 * 
 * WHILE
 * printf("FINLALIZADO: %i\n", n++);
    IO_toggleLed();
    CRONO_delayMs(100);
 * */