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

    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        sort(rbegin(items), rend(items));
        vector<bool> lookup(size(items));
        vector<int> stk;
        int64_t curr = 0, l = 0;
        for (int i = 0; i < k; ++i) {
            if (lookup[items[i][1] - 1]) {
                stk.emplace_back(items[i][0]);
            }
            curr += items[i][0];
            if (!lookup[items[i][1] - 1]) {
                lookup[items[i][1] - 1] = true;
                ++l;
            }
        }
        int64_t result = curr + l * l;
        for (int i = k; i < size(items); ++i) {
            if (lookup[items[i][1] - 1]) {
                continue;
            }
            if (empty(stk)) {
                break;
            }
            curr += items[i][0] - stk.back(); stk.pop_back();
            lookup[items[i][1] - 1] = true;
            ++l;
            result = max(result, curr + l * l);
        }
        return result;
    }

