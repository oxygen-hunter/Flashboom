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

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (size(sentence1) > size(sentence2)) {
            swap(sentence1, sentence2);
        }
        int count = 0;
        for (int step = 0; step < 2; ++step) {
            for (int i = 0; i <= size(sentence1); ++i) {
                char c1 = i != size(sentence1) ? sentence1[step == 0 ? i : size(sentence1) - 1 - i] : ' ';
                char c2 = i != size(sentence2) ? sentence2[step == 0 ? i : size(sentence2) - 1 - i] : ' ';
                if (c1 != c2) {
                    break;
                }
                if (c1 == ' ') {
                    ++count;
                }
            }
        }
        return count >= count_if(cbegin(sentence1), cend(sentence1),
                                 [](char x) { return x == ' '; }) + 1;
    }

