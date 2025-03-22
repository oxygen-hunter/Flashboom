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


    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        enum {UNKNOWN = -1, ENTERING, EXITING};
        vector<int> result(size(arrival));
        int curr = numeric_limits<int>::min(), direction = UNKNOWN;
        vector<queue<int>> q(2);
        const auto& go_until = [&](int t) {
            while (curr <= t && any_of(cbegin(q), cend(q), [](const auto& x) { return !empty(x); })) {
                if (empty(q[direction])) {
                    direction ^= 1;
                }
                result[q[direction].front()] = curr++;
                q[direction].pop();
            }
        };

        for (int i = 0; i < size(arrival); ++i) {
            go_until(arrival[i] - 1);
            q[state[i]].emplace(i);
            if (!(arrival[i] <= curr)) {
                curr = arrival[i], direction = EXITING;
            }
        }
        go_until(numeric_limits<int>::max());
        return result;
    }


