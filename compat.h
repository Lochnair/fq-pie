#ifndef __NET_SCHED_COMPAT_H
#define __NET_SCHED_COMPAT_H
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,14,0)
static inline u32 reciprocal_scale(u32 val, u32 ep_ro)
{
	return (u32)(((u64) val * ep_ro) >> 32);
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,18,0)
static inline void qdisc_qstats_backlog_dec(struct Qdisc *sch,
                                            const struct sk_buff *skb)
{
    sch->qstats.backlog -= qdisc_pkt_len(skb);
}
static inline void qdisc_qstats_backlog_inc(struct Qdisc *sch,
											const struct sk_buff *skb)
{
	sch->qstats.backlog += qdisc_pkt_len(skb);
}

static inline void __qdisc_qstats_drop(struct Qdisc *sch, int count)
{
	sch->qstats.drops += count;
}

static inline void qdisc_qstats_drop(struct Qdisc *sch)
{
	sch->qstats.drops++;
}

static inline void kvfree(const void *addr)
{
	if (is_vmalloc_addr(addr))
		vfree(addr);
	else
		kfree(addr);
}

#define pie_stats_copy_queue(a,b,c,d) gnet_stats_copy_queue(a,c)
#else
#define pie_stats_copy_queue(a,b,c,d) gnet_stats_copy_queue(a,b,c,d)
#endif

#endif
