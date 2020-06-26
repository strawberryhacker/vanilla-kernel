/// Copyright (C) StrawberryHacker

#include "types.h"
#include "scheduler.h"
#include "kernel_entry.h"
#include "thread.h"
#include "print.h"
#include "system_call.h"
#include "mm.h"
#include "sd_protocol.h"
#include "panic.h"
#include "fat32.h"

#include <stddef.h>


static void test_thread(void* arg) {
	while (1) {
		printl("Thread A says hello");
		syscall_thread_sleep(500);
	}
}

static void exit_thread(void* arg) {
	printl("Exit thread started\n");
}

int main(void) {
	kernel_entry();

	struct thread_info test_info = {
		.name       = "Test",
		.stack_size = 100,
		.thread     = test_thread,
		.class      = REAL_TIME,
		.arg        = NULL
	};

	struct thread_info exit_info = {
		.name       = "exit",
		.stack_size = 100,
		.thread     = exit_thread,
		.class      = REAL_TIME,
		.arg        = NULL
	};

	new_thread(&test_info);
	//new_thread(&exit_info);
	
	//fat32_thread(NULL);

	scheduler_start();
}
