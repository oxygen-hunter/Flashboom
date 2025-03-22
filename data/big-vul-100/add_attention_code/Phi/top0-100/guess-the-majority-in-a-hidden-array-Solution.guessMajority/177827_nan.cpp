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

    int guessMajority(ArrayReader &reader) {
        int count_a = 1, count_b = 0, idx_b = -1;
        const auto& value_0_1_2_3 = reader.query(0, 1, 2, 3);
        int value_0_1_2_i = -1;
        for (int i = reader.length() - 1; i >= 4; --i) {
            value_0_1_2_i = reader.query(0, 1, 2, i);
            if (value_0_1_2_i == value_0_1_2_3) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        const auto& value_0_1_2_4 = value_0_1_2_i;
        for (int i = 0; i < 3; ++i) {
            vector<int> a_b;
            for (int j = 0; j < 3; ++j) {
                if (j == i) {
                    continue;
                }
                a_b.emplace_back(j);
            }
            const auto& value_a_b_3_4 = reader.query(a_b[0], a_b[1], 3, 4);
            if (value_a_b_3_4 == value_0_1_2_4) {  // nums[i] == nums[3]
                ++count_a;
            } else {
                ++count_b;
                idx_b = i;
            }
        }
        if (count_a == count_b) {
            return -1;
        }
        return count_a > count_b ? 3 : idx_b;
    }

