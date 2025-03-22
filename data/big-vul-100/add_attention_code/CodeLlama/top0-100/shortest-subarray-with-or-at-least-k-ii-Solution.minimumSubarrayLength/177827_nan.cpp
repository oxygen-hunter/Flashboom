static struct posix_acl *jffs2_get_acl(struct inode *inode, int type)
 {
        struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
        struct posix_acl *acl;
	char *value = NULL;
	int rc, xprefix;

	switch (type) {
	case ACL_TYPE_ACCESS:
		acl = jffs2_iget_acl(inode, &f->i_acl_access);
		if (acl != JFFS2_ACL_NOT_CACHED)
			return acl;
		xprefix = JFFS2_XPREFIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		acl = jffs2_iget_acl(inode, &f->i_acl_default);
		if (acl != JFFS2_ACL_NOT_CACHED)
			return acl;
		xprefix = JFFS2_XPREFIX_ACL_DEFAULT;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}
	rc = do_jffs2_getxattr(inode, xprefix, "", NULL, 0);
	if (rc > 0) {
		value = kmalloc(rc, GFP_KERNEL);
		if (!value)
			return ERR_PTR(-ENOMEM);
		rc = do_jffs2_getxattr(inode, xprefix, "", value, rc);
	}
	if (rc > 0) {
		acl = jffs2_acl_from_medium(value, rc);
	} else if (rc == -ENODATA || rc == -ENOSYS) {
		acl = NULL;
	} else {
		acl = ERR_PTR(rc);
	}
	if (value)
		kfree(value);
	if (!IS_ERR(acl)) {
		switch (type) {
		case ACL_TYPE_ACCESS:
			jffs2_iset_acl(inode, &f->i_acl_access, acl);
			break;
		case ACL_TYPE_DEFAULT:
			jffs2_iset_acl(inode, &f->i_acl_default, acl);
			break;
		}
	}
	return acl;
}


    int minimumSubarrayLength(vector<int>& nums, int k) {
        const auto& bit_length = [](int x) {
            return (x ? std::__lg(x) : -1) + 1;
        };
    
        const int total = accumulate(cbegin(nums), cend(nums), 0, [](const auto& x, const auto& y) {
            return x | y;
        });
        if (total < k) {
            return -1;
        }
        vector<int> cnt(bit_length(total));
        const auto& update = [&](int x, int d, int curr) {
            for (int i = 0; (1 << i) <= x; ++i) {
                if (!(x & (1 << i))) {
                    continue;
                }
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
                cnt[i] += d;
                if (cnt[i] == 0) {
                    curr ^= 1 << i;
                }
            }
            return curr;
        };

        int result = size(nums);
        for (int right = 0, left = 0, curr = 0; right < size(nums); ++right) {
            curr = update(nums[right], +1, curr);
            for (; left <= right && curr >= k; ++left) {
                result = min(result, right - left + 1);
                curr = update(nums[left], -1, curr);
            }
        }
        return result;
    }


