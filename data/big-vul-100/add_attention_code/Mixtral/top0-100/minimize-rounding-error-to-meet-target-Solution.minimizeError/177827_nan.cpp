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

    string minimizeError(vector<string>& prices, int target) {
        vector<double> errors;
        int lower = 0, upper = 0;
        for (const auto& price : prices) {
            const auto& p = stod(price);
            lower += floor(p);
            upper += ceil(p);
            if (p != floor(p)) {
                errors.emplace_back(p - floor(p));
            }
        }
        if (target < lower || target > upper) {
            return "-1";
        }

        int lower_round_count = upper - target;
        nth_element(errors.begin(), errors.begin() + lower_round_count, errors.end());
        double min_error = 0.0;
        for (int i = 0; i < errors.size(); ++i) {
            if (i < lower_round_count) {
                min_error += errors[i];
            } else {
                min_error += 1.0 - errors[i];
            }
        }
        const auto& result = to_string(min_error);
        return result.substr(0, result.find(".") + 4);
    }

