#ifndef VHOST_NET_H
#define VHOST_NET_H

#include "net/net.h"
#include "hw/virtio/vhost-backend.h"

#define VHOST_NET_INIT_FAILED \
    "vhost-net requested but could not be initialized"

struct vhost_net;
typedef struct vhost_net VHostNetState;

typedef struct VhostNetOptions {
    VhostBackendType backend_type;
    NetClientState *net_backend;
    uint32_t busyloop_timeout;
    unsigned int nvqs;
    void *opaque;
} VhostNetOptions;

uint64_t vhost_net_get_max_queues(VHostNetState *net);
struct vhost_net *vhost_net_init(VhostNetOptions *options);

int vhost_net_start(VirtIODevice *dev, NetClientState *ncs,
                    int data_queue_pairs, int cvq);
void vhost_net_stop(VirtIODevice *dev, NetClientState *ncs,
                    int data_queue_pairs, int cvq);

void vhost_net_cleanup(VHostNetState *net);

uint64_t vhost_net_get_features(VHostNetState *net, uint64_t features);
void vhost_net_ack_features(VHostNetState *net, uint64_t features);

int vhost_net_get_config(struct vhost_net *net,  uint8_t *config,
                         uint32_t config_len);

int vhost_net_set_config(struct vhost_net *net, const uint8_t *data,
                         uint32_t offset, uint32_t size, uint32_t flags);
bool vhost_net_virtqueue_pending(VHostNetState *net, int n);
void vhost_net_virtqueue_mask(VHostNetState *net, VirtIODevice *dev,
                              int idx, bool mask);
int vhost_net_notify_migration_done(VHostNetState *net, char* mac_addr);
VHostNetState *get_vhost_net(NetClientState *nc);

int vhost_set_vring_enable(NetClientState * nc, int enable);

uint64_t vhost_net_get_acked_features(VHostNetState *net);

int vhost_net_set_mtu(struct vhost_net *net, uint16_t mtu);

int vhost_net_flow_create(struct vhost_net *net, struct virtio_net_flow_desc *flow_desc);
int vhost_net_flow_destroy(struct vhost_net *net, uint64_t flow_id);
int vhost_net_flow_query(struct vhost_net *net, struct virtio_net_flow_stats *flow_stats);
#endif
