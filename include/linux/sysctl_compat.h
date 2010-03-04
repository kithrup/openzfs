#ifndef _SPL_SYSCTL_COMPAT_H
#define _SPL_SYSCTL_COMPAT_H

#include <linux/sysctl.h>

/* proc_handler() / proc_do* API changes
 * 2.6.x  - 2.6.31: 6 args, prototype includes 'struct file *'
 * 2.6.32 - 2.6.y:  5 args, removed unused 'struct file *' from prototype
 *
 * Generic SPL_PROC_HANDLER() macro should be used for correct prototypes.
 * It will define the following function arguments which can and should be
 * used with the spl_proc_* helper macros.
 *
 *   struct ctl_table *table,
 *   int write,
 *   struct file *filp [2.6.31 and earlier kernels],
 *   void __user *buffer,
 *   size_t *lenp,
 *   loff_t *ppos,
 */
#ifdef HAVE_5ARGS_PROC_HANDLER

#define SPL_PROC_HANDLER(proc_handler)                                       \
static int                                                                   \
proc_handler(struct ctl_table *table, int write,                             \
             void __user *buffer, size_t *lenp, loff_t *ppos)              
                                                                           
#define spl_proc_dostring(table, write, filp, buffer, lenp, ppos)            \
	proc_dostring(table, write, buffer, lenp, ppos)                    
#define spl_proc_dointvec(table, write, filp, buffer, lenp, ppos)            \
	proc_dointvec(table, write, buffer, lenp, ppos)                    
#define spl_proc_dointvec_minmax(table, write, filp, buffer, lenp, ppos)     \
	proc_dointvec_minmax(table, write, buffer, lenp, ppos)                    
#define spl_proc_dointvec_jiffies(table, write, filp, buffer, lenp, ppos)    \
	proc_dointvec_jiffies(table, write, buffer, lenp, ppos)                    
#define spl_proc_dointvec_userhz_jiffies(table,write,filp,buffer,lenp,ppos)  \
	proc_dointvec_userhz_jiffies(table, write, buffer, lenp, ppos)                    
#define spl_proc_dointvec_ms_jiffies(table,write,filp,buffer,lenp,ppos)      \
	proc_dointvec_ms_jiffies(table, write, buffer, lenp, ppos)                    
#define spl_proc_doulongvec_minmax(table, write, filp, buffer, lenp, ppos)        \
	proc_doulongvec_minmax(table, write, buffer, lenp, ppos)
#define spl_proc_doulongvec_ms_jiffies_minmax(table,write,filp,buffer,lenp,ppos)  \
	proc_doulongvec_ms_jiffies_minmax(table, write, buffer, lenp, ppos)
                                                                           
#else /* HAVE_5ARGS_PROC_HANDLER */                                         
                                                                           
#define SPL_PROC_HANDLER(proc_handler)                                       \
static int                                                                   \
proc_handler(struct ctl_table *table, int write, struct file *filp,          \
             void __user *buffer, size_t *lenp, loff_t *ppos)              
                                                                           
#define spl_proc_dostring(table, write, filp, buffer, lenp, ppos)            \
	proc_dostring(table, write, filp, buffer, lenp, ppos)              
#define spl_proc_dointvec(table, write, filp, buffer, lenp, ppos)            \
	proc_dointvec(table, write, filp, buffer, lenp, ppos)
#define spl_proc_dointvec_minmax(table, write, filp, buffer, lenp, ppos)     \
	proc_dointvec_minmax(table, write, filp, buffer, lenp, ppos)
#define spl_proc_dointvec_jiffies(table, write, filp, buffer, lenp, ppos)    \
	proc_dointvec_jiffies(table, write, filp, buffer, lenp, ppos)
#define spl_proc_dointvec_userhz_jiffies(table,write,filp,buffer,lenp,ppos)  \
	proc_dointvec_userhz_jiffies(table, write, filp, buffer, lenp, ppos)
#define spl_proc_dointvec_ms_jiffies(table, write, filp, buffer, lenp, ppos) \
	proc_dointvec_ms_jiffies(table, write, filp, buffer, lenp, ppos)
#define spl_proc_doulongvec_minmax(table, write, filp, buffer, lenp, ppos)        \
	proc_doulongvec_minmax(table, write, filp, buffer, lenp, ppos)
#define spl_proc_doulongvec_ms_jiffies_minmax(table,write,filp,buffer,lenp,ppos)  \
	proc_doulongvec_ms_jiffies_minmax(table,write,filp,buffer,lenp,ppos)


#endif /* HAVE_5ARGS_PROC_HANDLER */

#endif /* _SPL_SYSCTL_COMPAT_H */
