/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/sched.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
       struct task_struct *task = NULL;

       printk(KERN_INFO "Loading Module\n");
       printk(KERN_INFO "Starting Listing tasks Linearly\n");

       for_each_process(task)
       {
            printk(KERN_INFO "Command: %-20s State: %ld\tProcess ID: %d\n", task->comm, task->state, task->pid);
       }

       printk(KERN_INFO "Stopping Listing tasks Linearly\n");

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Ryan Balachandran, 01427025");

