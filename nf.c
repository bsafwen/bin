#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <linux/printk.h>

void dump_skb(const struct sk_buff *skb)
{
	int i;
	pr_err("skb->len = %u\n", skb->len);
	for (i = 0; i + 8 < skb->len; i += 8) {
		pr_err("%d: %2X %2x %2X %2X %2X %2X %2X %2X", i, skb->data[i], skb->data[i+1], skb->data[i+2],skb->data[i+3],
				skb->data[i+4], skb->data[i+5], skb->data[i+6], skb->data[i+7]);
	}
	char str[256];
	int j = 0;
	while (i < skb->len) {
		sprintf(str + j, "%2X ", skb->data[i]);
		++i;
		if (i < skb->len)
			j += 3;
	}
	j++;
	str[j] = 0;
	pr_err("%s\n", str);
}

/* This function to be called by hook. */
static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct udphdr *udp_header;
	struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);    
	if (ip_header->protocol == 17) {
		if (skb->len > 3000)
			dump_skb(skb);
	}

	return NF_ACCEPT;
}

static struct nf_hook_ops nfho = {
	.hook       = hook_func,
	.hooknum    = NF_INET_LOCAL_IN,
	.pf         = PF_INET,
	.priority   = NF_IP_PRI_FIRST,
};

static int __init init_nf(void)
{
	pr_err("Register netfilter module.\n");
	int ret = nf_register_hook(&nfho);
	if (ret != 0) {
		pr_err("Registration failed.");
		return -1;
	}

	return 0;
}

static void __exit exit_nf(void)
{
	pr_err("Unregister netfilter module.\n");
	nf_unregister_hook(&nfho); 
}

module_init(init_nf);
module_exit(exit_nf);
MODULE_LICENSE("GPL");
