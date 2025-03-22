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


    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        const int R = size(grid), C = size(grid[0]);
        const int N = R * C;
        unordered_set<int> WALLS;
        int FOOD = -1, MOUSE_START = -1, CAT_START = -1;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == 'M') {
                    MOUSE_START = r * C + c;
                } else if (grid[r][c] == 'C') {
                    CAT_START = r * C + c;
                } else if (grid[r][c] == 'F') {
                    FOOD = r * C + c;
                } else if (grid[r][c] == '#') {
                    WALLS.emplace(r * C + c);
                }
            }
        }

        vector<vector<vector<int>>> graph(N, vector<vector<int>>(2));
        vector<int> jump = {mouseJump, catJump};
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == '#') {
                    continue;
                }
                int pos = r * C + c;
                for (const auto& t : {MOUSE, CAT}) {
                    for (const auto& [dr, dc] : directions) {
                        for (int d = 0; d <= jump[t - 1]; ++d) {
                            int nr = r + dr * d, nc = c + dc * d;
                            if (!(0 <= nr && nr < R && 0 <= nc && nc < C && grid[nr][nc] != '#')) {
                                break;
                            }
                            graph[pos][t - 1].emplace_back(nr * C + nc);
                        }
                    }
                }
            }
        }

        vector<vector<vector<int>>> degree(N, vector<vector<int>>(N, vector<int>(2)));
        for (int m = 0; m < size(graph); ++m) {
            for (int c = 0; c < size(graph); ++c) {
                // degree[m][c][MOUSE - 1] = size(graph[m][MOUSE - 1]);
                degree[m][c][CAT - 1] = size(graph[c][CAT - 1]);
            }
        }

        vector<vector<vector<int>>> color(N, vector<vector<int>>(N, vector<int>(2)));
        queue<tuple<int, int, int>> q1;
        // queue<tuple<int, int, int>> q2;
        for (int i = 0; i < size(graph); ++i) {
            if (WALLS.count(i) || i == FOOD) {
                continue;
            }
            color[FOOD][i][CAT - 1] = MOUSE;
            q1.emplace(FOOD, i, CAT);
            color[i][FOOD][MOUSE - 1] = CAT;
            // q2.emplace(i, FOOD, MOUSE);
            for (const auto& t : {MOUSE, CAT}) {
                color[i][i][t - 1] = CAT;
                // q2.emplace(i, i, t);
            }
        }
        while (!empty(q1)) {
            const auto [i, j, t] = q1.front(); q1.pop();
            for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
                if (color[ni][nj][nt - 1] != DRAW) {
                    continue;
                }
                if (t == CAT) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                    continue;
                }
                --degree[ni][nj][nt - 1];
                if (!degree[ni][nj][nt - 1]) {
                    color[ni][nj][nt - 1] = MOUSE;
                    q1.emplace(ni, nj, nt);
                }
            }
        }
        // while (!empty(q2)) {
        //     const auto [i, j, t] = q2.front(); q2.pop();
        //     for (const auto& [ni, nj, nt] : parents(graph, i, j, t)) {
        //         if (color[ni][nj][nt - 1] != DRAW) {
        //             continue;
        //         }
        //         if (t == MOUSE) {
        //             color[ni][nj][nt - 1] = CAT;
        //             q2.emplace(ni, nj, nt);
        //             continue;
        //         }
        //         --degree[ni][nj][nt - 1];
        //         if (!degree[ni][nj][nt - 1]) {
        //             color[ni][nj][nt - 1] = CAT;
        //             q2.emplace(ni, nj, nt);
        //         }
        //     }
        // }
        return color[MOUSE_START][CAT_START][MOUSE - 1] == MOUSE;
    }


