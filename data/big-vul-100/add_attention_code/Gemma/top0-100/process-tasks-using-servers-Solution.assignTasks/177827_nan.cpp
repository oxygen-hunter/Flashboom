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


    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        vector<pair<int, int>> idle;
        for (int i = 0; i < size(servers); ++i) {
            idle.emplace_back(servers[i], i);
        }
        make_heap(begin(idle), end(idle), greater<>());
        vector<tuple<int, int, int>> working;

        vector<int> result;
        for (int i = 0, t = 0; i < size(tasks); ++i) {
            t = !empty(idle) ? max(t, i) : get<0>(working.front());
            while (!empty(working) && get<0>(working.front()) <= t) {
                const auto [_, w, idx] = working.front(); pop_heap(begin(working), end(working), greater<>()); working.pop_back();
                idle.emplace_back(w, idx); push_heap(begin(idle), end(idle), greater<>());
            }
            const auto [w, idx] = idle.front(); pop_heap(begin(idle), end(idle), greater<>()); idle.pop_back();
            working.emplace_back(t + tasks[i], w, idx); push_heap(begin(working), end(working), greater<>());
            result.emplace_back(idx);
        }
        return result;
    }


