//
// Created by nirjal on 9/17/25.
//

#include <linux/module.h> /* Needed by all modules */

#include <linux/printk.h> /* Needed for pr_info() */

#include "utils.h"


MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Nirjal Bhurtel");
MODULE_DESCRIPTION("Learning kernel module programming in C. Trying by making a simple firewall.");

int init_module(void)
{
    pr_info("Hello world 1.\n");
    print_string_custom();
    /* A nonzero return means init_module failed; module can't be loaded. */
    return 0;
}

void cleanup_module(void)
{
    pr_info("Goodbye world 1.\n");
}

