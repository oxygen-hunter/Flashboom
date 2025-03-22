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

    int minimumVisitedCells(vector<vector<int>>& grid) {
        const int m = size(grid), n = size(grid[0]);
        vector<set<int>> bst1(m);
        vector<set<int>> bst2(n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                bst1[i].emplace(j);
                bst2[j].emplace(i);
            }
        }
        int d = 1, i = 0, j = 0;
        vector<pair<int, int>> q = {{i, j}};
        while (!empty(q)) {
            vector<pair<int, int>> new_q;
            for (const auto& [i, j] : q) {
                if (i == m - 1 && j == n - 1) {
                    return d;
                }
                for (auto it = bst1[i].lower_bound(j + 1);
                     it != end(bst1[i]) && *it <= j + grid[i][j];
                     it = bst1[i].erase(it)) {
                    new_q.emplace_back(i, *it);
                    bst2[*it].erase(i);
                }
                for (auto it = bst2[j].lower_bound(i + 1);
                     it != end(bst2[j]) && *it <= i + grid[i][j];
                     it = bst2[j].erase(it)) {
                    new_q.emplace_back(*it, j);
                    bst1[*it].erase(j);
                }
            }
            q = move(new_q);
            ++d;
        }
        return -1;
    }

