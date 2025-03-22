static int nfs_readlink_req(struct nfs_priv *npriv, struct nfs_fh *fh,
			    char **target)
{
	uint32_t data[1024];
	uint32_t *p;
	uint32_t len;
	struct packet *nfs_packet;

	/*
	 * struct READLINK3args {
	 * 	nfs_fh3 symlink;
	 * };
	 *
	 * struct READLINK3resok {
	 * 	post_op_attr symlink_attributes;
	 * 	nfspath3 data;
	 * };
	 *
	 * struct READLINK3resfail {
	 * 	post_op_attr symlink_attributes;
	 * }
	 *
	 * union READLINK3res switch (nfsstat3 status) {
	 * case NFS3_OK:
	 * 	READLINK3resok resok;
	 * default:
	 * 	READLINK3resfail resfail;
	 * };
	 */
	p = &(data[0]);
	p = rpc_add_credentials(p);

	p = nfs_add_fh3(p, fh);

	len = p - &(data[0]);

	nfs_packet = rpc_req(npriv, PROG_NFS, NFSPROC3_READLINK, data, len);
	if (IS_ERR(nfs_packet))
		return PTR_ERR(nfs_packet);

	p = (void *)nfs_packet->data + sizeof(struct rpc_reply) + 4;

 	p = nfs_read_post_op_attr(p, NULL);
 
 	len = ntoh32(net_read_uint32(p)); /* new path length */
 	p++;
 
 	*target = xzalloc(len + 1);
	return 0;
}


    void update(int key, int value) {
        int freq = 0;
        if (key_to_nodeit_.count(key)) {
            auto old_node = *key_to_nodeit_[key];        
            freq = std::get<FREQ>(old_node);
            freq_to_nodes_[freq].erase(key_to_nodeit_[key]);
            if (freq_to_nodes_[freq].empty()) {
                freq_to_nodes_.erase(freq);
                if (min_freq_ == freq) {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = min(min_freq_, ++freq);
        freq_to_nodes_[freq].emplace_back(key, value, freq);
        key_to_nodeit_[key] = prev(freq_to_nodes_[freq].end());
        ++size_;
    }


