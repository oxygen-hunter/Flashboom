NTSTATUS check_reduced_name_with_privilege(connection_struct *conn,
			const char *fname,
			struct smb_request *smbreq)
{
	NTSTATUS status;
	TALLOC_CTX *ctx = talloc_tos();
	const char *conn_rootdir;
	size_t rootdir_len;
	char *dir_name = NULL;
	const char *last_component = NULL;
	char *resolved_name = NULL;
	char *saved_dir = NULL;
        struct smb_filename *smb_fname_cwd = NULL;
        struct privilege_paths *priv_paths = NULL;
        int ret;
 
        DEBUG(3,("check_reduced_name_with_privilege [%s] [%s]\n",
                        fname,


	priv_paths = talloc_zero(smbreq, struct privilege_paths);
	if (!priv_paths) {
		status = NT_STATUS_NO_MEMORY;
		goto err;
	}

	if (!parent_dirname(ctx, fname, &dir_name, &last_component)) {
		status = NT_STATUS_NO_MEMORY;
		goto err;
	}

	priv_paths->parent_name.base_name = talloc_strdup(priv_paths, dir_name);
	priv_paths->file_name.base_name = talloc_strdup(priv_paths, last_component);

	if (priv_paths->parent_name.base_name == NULL ||
			priv_paths->file_name.base_name == NULL) {
		status = NT_STATUS_NO_MEMORY;
		goto err;
	}

	if (SMB_VFS_STAT(conn, &priv_paths->parent_name) != 0) {
		status = map_nt_error_from_unix(errno);
		goto err;
	}
	/* Remember where we were. */
	saved_dir = vfs_GetWd(ctx, conn);
	if (!saved_dir) {
		status = map_nt_error_from_unix(errno);
		goto err;
	}

	/* Go to the parent directory to lock in memory. */
	if (vfs_ChDir(conn, priv_paths->parent_name.base_name) == -1) {
		status = map_nt_error_from_unix(errno);
		goto err;
	}

	/* Get the absolute path of the parent directory. */
	resolved_name = SMB_VFS_REALPATH(conn,".");
	if (!resolved_name) {
		status = map_nt_error_from_unix(errno);
		goto err;
	}

	if (*resolved_name != '/') {
		DEBUG(0,("check_reduced_name_with_privilege: realpath "
			"doesn't return absolute paths !\n"));
		status = NT_STATUS_OBJECT_NAME_INVALID;
		goto err;
	}

	DEBUG(10,("check_reduced_name_with_privilege: realpath [%s] -> [%s]\n",
		priv_paths->parent_name.base_name,
		resolved_name));

	/* Now check the stat value is the same. */
	smb_fname_cwd = synthetic_smb_fname(talloc_tos(), ".", NULL, NULL);
	if (smb_fname_cwd == NULL) {
		status = NT_STATUS_NO_MEMORY;
		goto err;
	}

	if (SMB_VFS_LSTAT(conn, smb_fname_cwd) != 0) {
		status = map_nt_error_from_unix(errno);
		goto err;
	}

	/* Ensure we're pointing at the same place. */
	if (!check_same_stat(&smb_fname_cwd->st, &priv_paths->parent_name.st)) {
		DEBUG(0,("check_reduced_name_with_privilege: "
			"device/inode/uid/gid on directory %s changed. "
			"Denying access !\n",
			priv_paths->parent_name.base_name));
		status = NT_STATUS_ACCESS_DENIED;
		goto err;
	}

	/* Ensure we're below the connect path. */

	conn_rootdir = SMB_VFS_CONNECTPATH(conn, fname);
	if (conn_rootdir == NULL) {
		DEBUG(2, ("check_reduced_name_with_privilege: Could not get "
			"conn_rootdir\n"));
		status = NT_STATUS_ACCESS_DENIED;
		goto err;
	}
        }


    bool isRectangleCover(vector<vector<int>>& rectangles) {
        enum Location {L = 0, B = 1, R = 2, T = 3};
        int left = numeric_limits<int>::max(), bottom = numeric_limits<int>::max(),
            right = numeric_limits<int>::min(), top = numeric_limits<int>::min();
        for (const auto& rect : rectangles) {
            left = min(left, rect[L]);
            bottom = min(bottom, rect[B]);
            right = max(right, rect[R]);
            top = max(top, rect[T]);
        }

        using P = pair<pair<int, int>, int>;
        enum Corner {LB = 1, RB = 2, LT = 4, RT = 8};
        unordered_map<int, unordered_map<int, int>> corner_count;
        vector<P> corners{{{L, B}, LB}, {{R, B}, RB}, {{L, T}, LT}, {{R, T}, RT}};
        for (const auto& rect : rectangles) {
            for (const auto& corner : corners) {
                const auto x = rect[corner.first.first];
                const auto y = rect[corner.first.second];
                if (corner_count[x][y] & corner.second) {
                    return false;
                }
                corner_count[x][y] |= corner.second;
            }
        }

        bitset<16> is_valid;
        is_valid[LB | RB] = is_valid[LB | LT] = is_valid[RB | RT] = is_valid[LT | RT] = is_valid[LB | RB | LT | RT] = true;
        for (auto itx = corner_count.cbegin(); itx != corner_count.cend(); ++itx) {
            const auto x = itx->first;
            for (auto ity = itx->second.cbegin(); ity != itx->second.cend(); ++ity) {
                const auto y = ity->first;
                const auto mask = ity->second;
                if ((left < x && x < right) || (bottom < y && y < top)) {
                    if (!is_valid[mask]) {
                        return false;
                    }
                }
            }
        }

        return true;
    }


