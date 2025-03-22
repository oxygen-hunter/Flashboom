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

    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> lookup;
        for (const auto& pair : knowledge) {
            lookup[pair[0]] = pair[1];
        }
        string result, curr;
        bool has_pair = false;;
        for (int i = 0; i < size(s); ++i) {
            if (s[i] == '(') {
                has_pair = true;
            } else if (s[i] == ')') {
                has_pair = false;
                if (lookup.count(curr)) {
                    for (const auto& c : lookup[curr]) {
                        result.push_back(c);
                    }
                } else {
                    result.push_back('?');
                }
                curr.clear();
            } else if (has_pair) {
                curr.push_back(s[i]);
            } else {
                result.push_back(s[i]);
            }
        }
        return result;
    }

