#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/ioport.h>
#include<asm/io.h>
#include<linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Angad");

#ifndef DEBUG
	#define DEBUG
#endif

#ifndef DEVNAME
	#define DEVNAME "mydriver"
#endif

#ifndef BASE
	#define BASE 0x3F8
#endif

#ifndef RBR
	#define RBR 0x3F8
#endif

#ifndef THR
	#define THR 0x3F8
#endif

#ifndef DLL
	#define DLL 0x3F8
#endif

#ifndef DLM
	#define DLM 0x3F9
#endif

#ifndef IER
	#define IER 0x3F9
#endif

#ifndef IIR
	#define IIR 0x3FA
#endif

#ifndef FCR 
	#define FCR 0x3FA
#endif

#ifndef LCR
	#define LCR 0x3FB
#endif

#ifndef MCR
	#define MCR 0x3FC
#endif

#ifndef LSR
	#define LSR 0x3FD
#endif

#ifndef MSR
	#define MSR 0x3FE
#endif

#ifndef SCR
	#define SCR 0x3FF
#endif

#ifndef MAJORNO 
	#define MAJORNO 0
#endif

#ifndef MINORNO
	#define MINORNO 0
#endif

