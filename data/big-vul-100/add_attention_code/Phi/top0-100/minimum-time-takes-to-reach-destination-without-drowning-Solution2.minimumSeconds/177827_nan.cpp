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

    int minimumSeconds(vector<vector<string>>& land) {
        static const vector<pair<int, int>> DIRECTIONS {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<vector<int>> lookup1(size(land), vector<int>(size(land[0]), -1));
        vector<vector<int>> lookup2(size(land), vector<int>(size(land[0]), -1));
        vector<pair<int, int>> q1;
        vector<pair<int, int>> q2;
        for (int i = 0; i < size(land); ++i) {
            for (int j = 0; j < size(land[0]); ++j) {
                if (land[i][j] == "*") {
                    q1.emplace_back(i, j);
                    lookup2[i][j] = 0;
                } else if (land[i][j] == "S") {
                    q2.emplace_back(i, j);
                    lookup2[i][j] = 0;
                }
            }
        }
        while (!empty(q1) || !empty(q2)) {
            vector<pair<int, int>> new_q1;
            vector<pair<int, int>> new_q2;
            for (const auto& [i, j] : q1) {
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && land[ni][nj] != "D" && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup1[ni][nj] = 0;
                    new_q1.emplace_back(ni, nj);
                }
            }
            for (const auto& [i, j] : q2) {
                if (land[i][j] == "D") {
                    return lookup2[i][j];
                }
                for (const auto& [di, dj] : DIRECTIONS) {
                    const int ni = i + di, nj = j + dj;
                    if (!(0 <= ni && ni < size(land) && 0 <= nj && nj < size(land[0]) && land[ni][nj] != "X" && lookup2[ni][nj] == -1 && lookup1[ni][nj] == -1)) {
                        continue;
                    }
                    lookup2[ni][nj] = lookup2[i][j] + 1;
                    new_q2.emplace_back(ni, nj);
                }
            }
            q1 = move(new_q1);
            q2 = move(new_q2);
        }
        return -1;
    }

