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

    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        vector<int> lookup(size(nums), -1);
        for (int i = size(changeIndices) - 1; i >= 0; --i) {
            if (nums[changeIndices[i] - 1]) {
                lookup[changeIndices[i] - 1] = i;
            }
        }
        const int64_t total = accumulate(cbegin(nums), cend(nums), 0ll) + size(nums);
        const auto& check = [&](int t) {
            priority_queue<int, vector<int>, greater<int>> min_heap;
            int64_t total2 = 0, cnt = 0;
            for (int i = t - 1; i >= 0; --i) {
                if (i != lookup[changeIndices[i] - 1]) {
                    ++cnt;
                    continue;
                }
                min_heap.emplace(nums[changeIndices[i] - 1]);
                total2 += nums[changeIndices[i] - 1];
                if (cnt) {
                    --cnt;
                } else {
                    ++cnt;
                    total2 -= min_heap.top(); min_heap.pop();
                }
            }
            return total - (total2 + (size(min_heap))) <= cnt;
        };
    
        int64_t total2 = 0;
        for (int i = 0; i < size(nums); ++i) {
            total2 += lookup[i] != -1 ? 1 : nums[i];
        }
        int64_t left = total2 + size(nums), right = size(changeIndices);
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left <= size(changeIndices) ? left : -1;
    }

