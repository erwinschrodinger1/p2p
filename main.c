//
// Created by nirjal on 9/17/25.
//

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#include "utils.h"

#define MODULE_NAME "p2p"

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Nirjal Bhurtel");
MODULE_DESCRIPTION("Learning kernel module programming in C. Trying by making a simple firewall.");

// Proc file callbacks
static struct proc_dir_entry* entry, file1, file2;

struct file_data_t {
    int file_no;
};

struct file_data_t file1_data, file2_data;

int read_func(char* buffer, char** start, off_t off, int count, int* peof, void* data){
    struct file_data_t *file_data = (struct file_data_t*)data;

    if (file_data->file_no == 0){
        pr_info("reading file 1 file_data: %s", buffer);
    }
    else if(file_data->file_no == 1){
        pr_info("reading file 2 file_data: %s", buffer);
    }
    else{
        pr_info("reading: %s", buffer);
     }
    return 0;
}

int write_func(struct file* file, const char* buffer, unsigned long count, void* data){
    pr_info("writing: %s", buffer);
    return 0;
}

int init_module(void)
{
    pr_info("Hello world 1.\n");
    print_string_custom();
    entry = proc_mkdir(MODULE_NAME, NULL);
    if (entry == NULL) {
        return -ENOMEM;
    }
    entry->owner = THIS_MODULE;

    file1 = proc_create("file1", 0644, entry);
    if (file1 == NULL) {
        remove_proc_entry(MODULE_NAME, NULL);
        return -ENOMEM;
    }
    file1->owner = THIS_MODULE;
    file1_data.file_no = 0;
    file1->data = &file1_data;
    file1->read_proc = read_func;
    file1->write_proc = write_func;

    file2 = proc_create("file2", 0644, entry);
    if (file2 == NULL) {
            remove_proc_entry("file1", entry);
            return -ENOMEM;
    }

    file2->owner = THIS_MODULE;
    file2_data.file_no = 1;
    file2->data = &file2_data;
    file2->read_proc = read_func;
    file2->write_proc = write_func;

    /* A nonzero return means init_module failed; module can't be loaded. */
    return 0;
}

void cleanup_module(void)
{
    remove_proc_entry("file2", entry);
    remove_proc_entry("file1", entry);
    remove_proc_entry(MODULE_NAME, NULL);

    pr_info("Goodbye world 1.\n");
}

