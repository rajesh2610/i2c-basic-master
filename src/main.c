/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};
static uint8_t read_buffer[DATA_LENGTH];
#define SLAVE_ADDRESS 0x40
#define TIMEOUT 1000
#define CONF_MASTER_SDA_PINMUX  PINMUX_PA08_SERCOM2_PAD0
#define CONF_MASTER_SCK_PINMUX  PINMUX_PA09_SERCOM2_PAD1
#define CONF_I2C_MASTER_MODULE   SERCOM2

struct i2c_master_module i2c_master_instance;


void configure_i2c_master(void)
{
	/* Initialize config structure and software module. */
	struct i2c_master_config config_i2c_master;
	i2c_master_get_config_defaults(&config_i2c_master);
	/* Change buffer timeout to something longer. */
	config_i2c_master.buffer_timeout = 10000;
	#if SAMR30
	config_i2c_master.pinmux_pad0    = CONF_MASTER_SDA_PINMUX;
	config_i2c_master.pinmux_pad1    = CONF_MASTER_SCK_PINMUX;
	#endif
	/* Initialize and enable device with config. */
	i2c_master_init(&i2c_master_instance, CONF_I2C_MASTER_MODULE, &config_i2c_master);
	i2c_master_enable(&i2c_master_instance);
}


int main (void)
{
	system_init();

	/* Insert application code here, after the board has been initialized. */

	/* This skeleton code simply sets the LED to the state of the button. */
	
	 /* Configure device and enable. */
	 configure_i2c_master();
	 /* Timeout counter. */
	 uint16_t timeout = 0;
	 /* Init i2c packet. */
	 struct i2c_master_packet packet = {
		 .address     = SLAVE_ADDRESS,
		 .data_length = DATA_LENGTH,
		 .data        = write_buffer,
		 .ten_bit_address = false,
		 .high_speed      = false,
		 .hs_master_code  = 0x0,
	 };
	    /* Write buffer to slave until success. */
	    while (i2c_master_write_packet_wait(&i2c_master_instance, &packet) !=
	    STATUS_OK) {
		    /* Increment timeout counter and check if timed out. */
		    if (timeout++ == TIMEOUT) {
			    break;
		    }
	    }
	    ///* Read from slave until success. */
	    //packet.data = read_buffer;
	    //while (i2c_master_read_packet_wait(&i2c_master_instance, &packet) !=
	    //STATUS_OK) {
		    ///* Increment timeout counter and check if timed out. */
		    //if (timeout++ == TIMEOUT) {
			    //break;
			    //
	
	
	//while (1) {
		///* Is button pressed? */
		//if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			///* Yes, so turn LED on. */
			//port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		//} else {
			///* No, so turn LED off. */
			//port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		//}
	//}
}
