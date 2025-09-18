//
// Created by nirjal on 9/17/25.
//
#include "utils.h"
#include <linux/printk.h> /* Needed for pr_info() */

void print_string_custom(void){
    pr_info("printing string from another file\n");
    return;
}

