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


    vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
        unordered_set<int64_t> lookup;
        unordered_map<int, int> row, col, diag, anti;
        for (const auto& lamp : lamps) {
            int r, c;
            tie(r, c) = make_pair(lamp[0], lamp[1]);
            if (!lookup.emplace(static_cast<int64_t>(r) * N + c).second) {
                continue;
            }
            ++row[r];
            ++col[c];
            ++diag[r - c];
            ++anti[r + c];
        }
        
        vector<int> result;
        for (const auto& query : queries) {
            int r, c;
            tie(r, c) = make_pair(query[0], query[1]);
            if (!(row[r] || col[c] || diag[r - c] || anti[r + c])) {
                result.emplace_back(0);
                continue;
            }
            result.emplace_back(1);
            for (int nr = max(r - 1, 0); nr <= min(r + 1, N - 1); ++nr) {
                for (int nc = max(c - 1, 0); nc <= min(c + 1, N - 1); ++nc) {
                    if (!lookup.erase(static_cast<int64_t>(nr) * N + nc)) {
                        continue;
                    }
                    --row[nr];
                    --col[nc];
                    --diag[nr - nc];
                    --anti[nr + nc];
                }
            }
        }
        return result;
    }


