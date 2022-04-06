/*
 * aesdchar.h
 *
 *  Created on: Oct 23, 2019
 *      Author: Dan Walkes
 */

#ifndef AESD_UART_DRIVER_AESDCHAR_H_
#define AESD_UART_DRIVER_AESDCHAR_H_

#define AESD_DEBUG 1  //Remove comment on this line to enable debug

#undef PDEBUG             /* undef it, just in case */
#ifdef AESD_DEBUG
#  ifdef __KERNEL__
     /* This one if debugging is on, and kernel space */
#    define PDEBUG(fmt, args...) printk( KERN_ALERT "aesdchar: " fmt, ## args)
#  else
     /* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stderr, fmt, ## args)
#  endif
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

// Include the circular buffer header file
#include "aesd-uart-circular-buffer.h"

struct aesd_dev
{
	/**
	 * TODO: Add structure(s) and locks needed to complete assignment requirements
	 * 
	 * 	Add circular buffer structure
	 * 	Add working (current) aesd_buffer_entry value
	 *  Add locking primitive (mutex)
	 */
	
	struct aesd_circular_buffer aesd_cbuf;
	struct aesd_buffer_entry *aesd_cb_entry;

	struct mutex lock;

	struct cdev cdev;	  /* Char device structure	*/
};


#endif /* AESD_UART_DRIVER_AESDCHAR_H_ */
