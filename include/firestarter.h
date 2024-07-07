/*
 * Project Name: Firestarter
 * Copyright (c) 2024 Henrik Olsson
 *
 * Permission is hereby granted under MIT license.
 */

#ifndef FIRESTARTER_H
#define FIRESTARTER_H
#include <stdint.h>
#include <stdbool.h>


#define DATA_BUFFER_SIZE 256

#define STATE_IDLE 0
#define STATE_READ 1
#define STATE_WRITE 2
#define STATE_ERASE 3
#define STATE_CHECK_ERASED 4
// #define STATE_READ_VPE 10
#define STATE_READ_VPP 11
#define STATE_READ_VCC 12 
#define STATE_VERSION 13
#define STATE_CONFIG 14

#define STATE_DONE 99
#define STATE_ERROR 100

#define RESPONSE_CODE_OK 0
#define RESPONSE_CODE_WARNING 1
#define RESPONSE_CODE_ERROR 2

typedef struct bus_config {
	uint8_t address_lines[19]; // Array mapping address lines
	uint8_t rw_line;           // RW line mapping
	uint8_t vpp_line;		  // VPP line mapping
} bus_config_t;


typedef struct firestarter_handle {
	uint8_t verbose;
	uint8_t state;
	uint8_t init;
	uint8_t response_code;
	char response_msg[64];
	uint8_t mem_type;
	uint32_t protocol;
	uint8_t pins;
	uint32_t mem_size;
	uint32_t address;
	float vpp;
	uint32_t pulse_delay;
	uint8_t can_erase;
	uint8_t skip_erase;
	uint8_t blank_check;
	uint16_t chip_id;
	char data_buffer[DATA_BUFFER_SIZE];
	uint32_t data_size;
	bus_config_t bus_config;

	void (*firestarter_set_data)(struct firestarter_handle*, uint32_t, uint8_t);
	void (*firestarter_write_init)(struct firestarter_handle*);
	void (*firestarter_write_data)(struct firestarter_handle*);
	uint8_t(*firestarter_get_data)(struct firestarter_handle*, uint32_t);
	void(*firestarter_read_data)(struct firestarter_handle*);
	void (*firestarter_check_erased)(struct firestarter_handle*);
	void (*firestarter_set_address)(struct firestarter_handle*, uint32_t);
	void (*firestarter_set_control_register)(struct firestarter_handle*, uint8_t, bool);
	bool (*firestarter_get_control_register)(struct firestarter_handle*, uint8_t);

} firestarter_handle_t;


#endif // FIRESTARTER_H