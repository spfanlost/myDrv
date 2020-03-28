/**
 * @file char_drv.h
 * @author meng_yu (imyumeng@qq.com)
 * @brief 
 * @version 0.1
 * @date 2020-03-14
 * 
 * @copyright imyumeng@qq.com Copyright (c) 2020
 * 
 */

#define APPNAME         "my_drv"
#define LEVEL           APPNAME

#define DEBUG
#define LOG_ERR(fmt, ...)    \
    printk("%s-err:%s:%d: \033[31m" fmt "\033[0m\r\n", \
    LEVEL, __FILE__, __LINE__, ## __VA_ARGS__)
#ifdef DEBUG
#define LOG_DBG(fmt, ...)    \
    printk("%s-dbg:%s:%d: " fmt "\r\n", \
    LEVEL, __FILE__, __LINE__, ## __VA_ARGS__)
#else
#define LOG_DBG(fmt, ...)
#endif

