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

    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int64_t> diffs(size(nums1));
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = abs(nums1[i] - nums2[i]);
        }
        sort(rbegin(diffs), rend(diffs));
        int64_t k = min(static_cast<int64_t>(k1) + k2, accumulate(cbegin(diffs), cend(diffs), static_cast<int64_t>(0)));
        const auto& check = [&](int x) {
            return accumulate(cbegin(diffs), cend(diffs), 0ll,
                              [&](const auto& total, const auto& d) {
                                  return total + max(d - x, static_cast<int64_t>(0));
                              }) <= k;
        };
        int64_t left = 0, right = diffs[0];
        while (left <= right) {
            const int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        k -= accumulate(cbegin(diffs), cend(diffs), 0ll,
                        [&](const auto& total, const auto& d) {
                            return total + max(d - left, static_cast<int64_t>(0));
                        });
        for (int i = 0; i < size(diffs); ++i) {
            diffs[i] = min(diffs[i], left) - int(i < k);
        }
        return accumulate(cbegin(diffs), cend(diffs), 0ll,
                          [](const auto& total, const auto& d) {
                              return total + d * d;
                          });
    }

