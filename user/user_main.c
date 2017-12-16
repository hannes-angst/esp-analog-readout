/*
 *  Example of working sensor DHT22 (temperature and humidity) and send data on the service thingspeak.com
 *  https://thingspeak.com
 *
 *  For a single device, connect as follows:
 *  DHT22 1 (Vcc) to Vcc (3.3 Volts)
 *  DHT22 2 (DATA_OUT) to ESP Pin GPIO2
 *  DHT22 3 (NC)
 *  DHT22 4 (GND) to GND
 *
 *  Between Vcc and DATA_OUT need to connect a pull-up resistor of 10 kOh.
 *
 *  (c) 2015 by Mikhail Grigorev <sleuthhound@gmail.com>
 *
 */

#include <user_interface.h>
#include <osapi.h>
#include <c_types.h>
#include <mem.h>
#include <os_type.h>
#include "user_config.h"
#include <gpio.h>

LOCAL os_timer_t ldr_timer;

const char *FlashSizeMap[] =
{
		"512 KB (256 KB + 256 KB)",	// 0x00
		"256 KB",			// 0x01
		"1024 KB (512 KB + 512 KB)", 	// 0x02
		"2048 KB (512 KB + 512 KB)"	// 0x03
		"4096 KB (512 KB + 512 KB)"	// 0x04
		"2048 KB (1024 KB + 1024 KB)"	// 0x05
		"4096 KB (1024 KB + 1024 KB)"	// 0x06
};


static void ICACHE_FLASH_ATTR ldr_cb(void *arg)
{
	uint16 adc = system_adc_read();
	INFO("%d\n", adc);
}


static void ICACHE_FLASH_ATTR app_init(void) {
	INFO("\n==== System info: ====\n");
	INFO("SDK version:%s rom %d\n", system_get_sdk_version(), system_upgrade_userbin_check());
	INFO("Time = %ld\n", system_get_time());
	INFO("Chip id = 0x%x\n", system_get_chip_id());
	INFO("CPU freq = %d MHz\n", system_get_cpu_freq());
	INFO("Flash size map = %s\n", FlashSizeMap[system_get_flash_size_map()]);
	INFO("Free heap size = %d\n", system_get_free_heap_size());
	INFO("==== End System info ====\n");
	// Set up a timer to send the message
	os_timer_disarm(&ldr_timer);
	os_timer_setfn(&ldr_timer, (os_timer_func_t *)ldr_cb, (void *)0);
	os_timer_arm(&ldr_timer, DATA_SEND_DELAY, 1);

	INFO("System init done.\n");
}

void user_init(void) {
	// Enable system messages
	system_set_os_print(1);
	gpio_init();
	system_init_done_cb(app_init);
}
