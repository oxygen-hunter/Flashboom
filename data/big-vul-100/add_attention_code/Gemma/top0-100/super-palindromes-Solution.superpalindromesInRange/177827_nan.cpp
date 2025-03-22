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


    int superpalindromesInRange(string L, string R) {
        const auto K = static_cast<int>(pow(10, (R.length() + 1) * 0.25));
        const int64_t l = stol(L), r = stol(R);
        int result = 0;

        // count odd length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s.substr(1));
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        // count even length
        for (int k = 0; k < K; ++k) {
            const string s = to_string(k), rev_s(s.rbegin(), s.rend());
            int64_t v = stol(s + rev_s);
            v *= v;
            if (v > r) {
                break;
            }
            if (v >= l && is_palindrome(v)) {
                ++result;
            }
        }

        return result;
    }


