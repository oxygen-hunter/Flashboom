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

    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        static const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> min_heap;
        min_heap.emplace(grid[0][0], 0, 0);
        vector<vector<bool>> lookup(size(grid), vector<bool>(size(grid[0])));
        lookup[0][0] = true;
        unordered_map<int, int> cnt;
        int mx = 0;
        while (!empty(min_heap)) {
            const auto [curr, i, j] = min_heap.top(); min_heap.pop();
            mx = max(mx, curr);
            ++cnt[mx];
            for (const auto& [di, dj] : directions) {
                const int ni = i + di, nj = j + dj;
                if (!(0 <= ni && ni < size(grid) &&
                      0 <= nj && nj < size(grid[0]) &&
                      !lookup[ni][nj])) {
                    continue;
                }
                lookup[ni][nj] = true;
                min_heap.emplace(grid[ni][nj], ni, nj);
            }
        }
        vector<int> vals;
        for (const auto& [k, _] : cnt) {
            vals.emplace_back(k);
        }
        sort(begin(vals), end(vals));
        vector<int> prefix(size(vals) + 1);
        for (int i = 0; i < size(vals); ++i) {
            prefix[i + 1] = prefix[i] + cnt[vals[i]];
        }
        vector<int> result(size(queries));
        for (int i = 0; i < size(queries); ++i) {
            result[i] = prefix[distance(cbegin(vals), lower_bound(cbegin(vals), cend(vals), queries[i]))];
        }
        return result;
    }

