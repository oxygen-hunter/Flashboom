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

    int minimumChanges(string s, int k) {
        vector<vector<int>> divisors(size(s) + 1);
        for (int i = 1; i < size(divisors); ++i) {  // Time: O(nlogn), Space: O(nlogn)
            for (int j = i + i; j < size(divisors); j += i) {
                divisors[j].emplace_back(i);
            }
        }

        const auto& dist = [&](int left, int right, int d) {
            int result = 0;
            for (int i = 0; i < (right - left + 1) / 2; ++i) {
                if (s[left + i] != s[right - ((i / d + 1) * d - 1) + (i % d)]) {
                    ++result;
                }
            }
            return result;
        };

        const auto& min_dist = [&](int left, int right) {  // Time: O(nlogn)
            int result = size(s);
            for (const auto& d : divisors[right - left + 1]) {
                result = min(result, dist(left, right, d));
            }
            return result;
        };
            
        vector<vector<int>> dp(size(s) + 1, vector<int>(k + 1, size(s)));
        dp[0][0] = 0;
        for (int i = 0; i < size(s); ++i) {  // Time: O(n^2 * nlogn + n^2 * k), Space: O(n * k)
            for (int j = 0; j < i; ++j) {
                const int c = min_dist(j, i);
                for (int l = 0; l < k; ++l) {
                    dp[i + 1][l + 1] = min(dp[i + 1][l + 1], dp[j][l] + c);
                }
            }
        }
        return dp[size(s)][k];
    }

