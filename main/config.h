/** \file config.h
 *  Mar 2022
 *  Maestría en SIstemas Embebidos - Sistemas embebidos distribuidos
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* configuración WIFI */
#define ESP_WIFI_SSID "WELS_LIBI"     // CONFIG_ESP_WIFI_SSID  // "SSID wifi"
#define ESP_WIFI_PASS "w@2801(-)2206@j"     // CONFIG_ESP_WIFI_PASS  // "pass wifi"

/*  Configuracion MQTT  */
#define PORT_MQTT 1883            //CONFIG_PORT_MQTT      // default
#define IP_BROKER_MQTT "test.mosquitto.org"    //CONFIG_IP_BROKER_MQTT // Broker MQTT

/*  configuración IO */
#define BLINK_GPIO CONFIG_BLINK_GPIO  // port 2 para NodeMcu-23S
#define PWM_PORT 25          // puerto de salida de pwm

/* Configuración SD  */

/* Configuración CRONO  */
#define SAMPLES_SIZE 1500

typedef struct
{
    volatile int active_button;/* data */
    volatile int active_led;
    volatile int adc;
}data_t;


#endif
