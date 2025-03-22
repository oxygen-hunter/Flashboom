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


    int palindromePartition(string s, int k) {
        // dp1[i][j]: minimum number of changes to make s[i, j] palindrome
        vector<vector<int>> dp1(s.length(), vector<int>(s.length()));
        for (int l = 1; l <= s.length(); ++l) {
            for (int i = 0; i + l <= s.length(); ++i) {
                int j = i + l - 1;
                if (i == j - 1) {
                    dp1[i][j] = s[i] == s[j] ? 0 : 1;
                }  else if (i != j) {
                    dp1[i][j] = s[i] == s[j] ? dp1[i + 1][j - 1] : dp1[i + 1][j - 1] + 1;
                }
            }
        }
        // dp2[d][i]: minimum number of changes to divide s[0, i] into d palindromes
        vector<vector<int>> dp2(2, vector<int>(s.length(), numeric_limits<int>::max()));
        dp2[1] = dp1[0];
        for (int d = 2; d <= k; ++d) {
            dp2[d % 2] = vector<int>(s.length(), numeric_limits<int>::max());
            for (int i = d - 1; i < s.length(); ++i) {
                for (int j = d - 2; j < i; ++j) {
                    dp2[d % 2][i] = min(dp2[d % 2][i], dp2[(d - 1) % 2][j] + dp1[j + 1][i]);
                }
            }
        }
        return dp2[k % 2][s.length() - 1];
    }


