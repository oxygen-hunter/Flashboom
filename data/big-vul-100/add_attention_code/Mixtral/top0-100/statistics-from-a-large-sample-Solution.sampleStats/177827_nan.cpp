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

    vector<double> sampleStats(vector<int>& count) {
        const double mi = distance(count.cbegin(), find_if(count.cbegin(), count.cend(), 
                                   [](int x) { return x != 0; }));
        
        const double ma = count.size() - 1 - 
                          distance(count.crbegin(), find_if(count.crbegin(), count.crend(), 
                                   [](int x) { return x != 0; }));
        
        const auto& n = accumulate(count.cbegin(), count.cend(), 0);
        double total = 0.0;
        for (int i = 0; i < count.size(); ++i) {
            total += double(i) * count[i];
        }
        const double mean = total / n;
        
        const double mode = distance(count.cbegin(), max_element(count.cbegin(), count.cend()));
        
        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }
        const auto& median1 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 1) / 2));
        const auto& median2 = distance(count.cbegin(), lower_bound(count.cbegin(), count.cend(), (n + 2) / 2));
        const double median = (median1 + median2) / 2.0;
        
        return {mi, ma, mean, median, mode};
    }

