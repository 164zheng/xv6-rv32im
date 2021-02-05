#include "types.h"
#include "mbuf.h"
#include "ip.h"
#include "udp.h"
#include "defs.h"

static uint
is_udp_packet_valid(struct udp_hdr *hdr)
{
  // TODO: check validity.
  // just return 1 for now.
  return 1;
}

void
udp_rx(struct mbuf *m, uint16 len, struct ip_hdr *iphdr)
{
  struct udp_hdr *udphdr = (struct udp_hdr*)mbuf_pop(m, sizeof(struct udp_hdr*));
  if (!is_udp_packet_valid(udphdr)) {
    return;
  }
  len -= sizeof(*udphdr);
  mbuf_trim(m, m->len - len);

  uint32 src_ip_addr = iphdr->src_ip_addr;
  uint16 src_port = udphdr->src_port;
  uint16 dst_port = udphdr->dst_port;
  socket_recv_udp(m, src_ip_addr, src_port, dst_port);
}