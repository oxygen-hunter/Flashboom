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

    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        const int n = size(colors);
        set<int> bst;
        BIT bit1(n + 1), bit2(n + 1);
        const auto& update = [&](int i, int d) {
            if (d == +1) {
                bst.emplace(i);
                if (size(bst) == 1) {
                    bit1.add(n, +1);
                    bit2.add(n, +n);
                }
            }
            auto curr = bst.find(i);
            auto prv = prev(curr != begin(bst) ? curr : end(bst));
            auto nxt = next(curr);
            if (nxt == end(bst)) {
                nxt = begin(bst);
            }
            if (size(bst) != 1) {
                int l = ((*nxt) - (*prv) + (n - 1)) % n + 1;
                bit1.add(l, d * -1);
                bit2.add(l, d * -l);
                l = ((*curr) - (*prv) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
                l = ((*nxt) - (*curr) + n) % n;
                bit1.add(l, d * +1);
                bit2.add(l, d * +l);
            }
            if (d == -1) {
                if (size(bst) == 1) {
                    bit1.add(n, -1);
                    bit2.add(n, -n);
                }
                bst.erase(curr);
            }
        };

        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (colors[i] == colors[(i + 1) % n]) {
                update(i, +1);
            }
        }
        for (const auto &q : queries) {
            if (q[0] == 1) {
                const int l = q[1];
                result.emplace_back(!empty(bst) ? (bit2.query(n) - bit2.query(l - 1)) - 
                                                  (l - 1) * (bit1.query(n) - bit1.query(l - 1)) : n);
                continue;
            }
            const int i = q[1];
            if (colors[i] == q[2]) {
                continue;
            }
            colors[i] = q[2];
            update((i - 1 + n) % n, colors[i] == colors[(i - 1 + n) % n] ? +1 : -1);
            update(i, colors[i] == colors[(i + 1) % n] ? +1 : -1);
        }
        return result;
    }

