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

    string largestPalindrome(int n, int k) {
        const auto& powmod = [](uint32_t a, uint32_t b, uint32_t mod) {
            a %= mod;
            uint64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % mod;
                }
                a = uint64_t(a) * a % mod;
                b >>= 1;
            }
            return result;
        };

        const auto& inv = [&](int x, int p) {
            return powmod(x, p - 2, p);
        };

        const auto& f = [&](int l) {
            static const int p = 7;
            string result(l, '9');
            if (l == 0) {
                return result;
            }
            int curr = 0;
            for (const auto& x : result) {
                curr = (curr * 10 + (x - '0')) % p;
            }
            // l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            // l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            int i = 9 - (curr * inv(l % 2 == 0 ? 11 : 1, p) * inv(powmod(10, l / 2 - (l % 2 == 0 ? 1 : 0), p), p)) % p;
            if (i <= 2) {
                i += p;
            }
            result[l / 2] = result[l / 2 - (l % 2 == 0 ? 1 : 0)] = '0' + i;
            return result;
        };

        if (k == 1 || k == 3 || k == 9) {
            return string(n, '9');
        }
        if (k == 2 || k == 4 || k == 8) {
            k = min(k, 6);
            if (n <= k) {
                return string(n, '8');
            }
            const int l = k / 2;
            return string(l, '8') + string(n - k, '9') + string(l, '8');
        }
        if (k == 5) {
            if (n <= 2) {
                return string(n, '5');
            }
            return string(1, '5') + string(n - 2, '9') + string(1, '5');
        }
        if (k == 6) {
            if (n <= 2) {
                return string(n, '6');
            }
            if (n % 2) {
                const int l = n / 2 - 1;
                return string(1, '8') + string(l, '9') + string(1, '8') + string(l, '9') + string(1, '8');
            }
            const int l = n / 2 - 2;
            return string(1, '8') + string(l, '9') + string(2, '7') + string(l, '9') + string(1, '8');
        }
        const int l = n / 12, r = n % 12;
        return string(l * 6, '9') + f(r) + string(l * 6, '9');  // 999999%7 = 0
    }

