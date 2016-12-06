/*
 *      IP Virtual Server
 *      data structure and functionality definitions
 */

 //If we are on a new enough version to use IPV6 the header is
 // located here
#include <uapi/linux/ip_vs.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/types.h>	/* For __beXX types in userland */

#ifdef LIBIPVS_USE_NL
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
//#include <libnl3/netlink/netlink.h>
//#include <libnl3/netlink/genl/genl.h>
//#include <libnl3/netlink/genl/ctrl.h>

#endif

union nf_inet_addr {
	__u32           all[4];
	__be32          ip;
	__be32          ip6[4];
	struct in_addr  in;
	struct in6_addr in6;
};

/*
 *	IPVS statistics object (for user space), 64-bit
 */
struct ip_vs_stats64 {
	__u64			conns;		/* connections scheduled */
	__u64			inpkts;		/* incoming packets */
	__u64			outpkts;	/* outgoing packets */
	__u64			inbytes;	/* incoming bytes */
	__u64			outbytes;	/* outgoing bytes */

	__u64			cps;		/* current connection rate */
	__u64			inpps;		/* current in packet rate */
	__u64			outpps;		/* current out packet rate */
	__u64			inbps;		/* current in byte rate */
	__u64			outbps;		/* current out byte rate */
};

struct ip_vs_service_entry1 {
	/* which service: user fills in these */
	u_int16_t		protocol;
	__be32			__addr_v4;	/* virtual address - internal use only*/
	__be16			port;
	u_int32_t		fwmark;		/* firwall mark of service */

	/* service options */
	char			sched_name[IP_VS_SCHEDNAME_MAXLEN];
	unsigned		flags;          /* virtual service flags */
	unsigned		timeout;	/* persistent timeout */
	__be32			netmask;	/* persistent netmask */

	/* number of real servers */
	unsigned int		num_dests;

	/* statistics */
	struct ip_vs_stats_user stats;

	u_int16_t		af;
	union nf_inet_addr	addr;
	char			pe_name[IP_VS_PENAME_MAXLEN];

	/* statistics, 64-bit */
	struct ip_vs_stats64	stats64;
};

struct ip_vs_dest_entry1 {
	__be32			__addr_v4;	/* destination address - internal use only */
	__be16			port;
	unsigned		conn_flags;	/* connection flags */
	int			weight;		/* destination weight */

	u_int32_t		u_threshold;	/* upper threshold */
	u_int32_t		l_threshold;	/* lower threshold */

	u_int32_t		activeconns;	/* active connections */
	u_int32_t		inactconns;	/* inactive connections */
	u_int32_t		persistconns;	/* persistent connections */

	/* statistics */
	struct ip_vs_stats_user stats;
	u_int16_t		af;
	union nf_inet_addr	addr;

	/* statistics, 64-bit */
	struct ip_vs_stats64	stats64;
};

struct ip_vs_get_dests1 {
	/* which service: user fills in these */
	u_int16_t		protocol;
	__be32			__addr_v4;	/* virtual address - internal use only */
	__be16			port;
	u_int32_t		fwmark;		/* firwall mark of service */

	/* number of real servers */
	unsigned int		num_dests;
	u_int16_t		af;
	union nf_inet_addr	addr;

	/* the real servers */
	struct ip_vs_dest_entry1	entrytable[0];
};

/* The argument to IP_VS_SO_GET_SERVICES */
struct ip_vs_get_services1 {
	/* number of virtual services */
	unsigned int		num_services;

	/* service table */
	struct ip_vs_service_entry1 entrytable[0];
};


#ifdef LIBIPVS_USE_NL
extern struct nla_policy ipvs_cmd_policy[IPVS_CMD_ATTR_MAX + 1];
extern struct nla_policy ipvs_service_policy[IPVS_SVC_ATTR_MAX + 1];
extern struct nla_policy ipvs_dest_policy[IPVS_DEST_ATTR_MAX + 1];
extern struct nla_policy ipvs_stats_policy[IPVS_STATS_ATTR_MAX + 1];
extern struct nla_policy ipvs_info_policy[IPVS_INFO_ATTR_MAX + 1];
extern struct nla_policy ipvs_daemon_policy[IPVS_DAEMON_ATTR_MAX + 1];
#endif

/* End of Generic Netlink interface definitions */
