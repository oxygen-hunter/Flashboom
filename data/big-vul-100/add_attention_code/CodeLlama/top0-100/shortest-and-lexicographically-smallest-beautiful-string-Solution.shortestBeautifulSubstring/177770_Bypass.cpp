int read_ndx_and_attrs(int f_in, int f_out, int *iflag_ptr, uchar *type_ptr,
		       char *buf, int *len_ptr)
{
	int len, iflags = 0;
	struct file_list *flist;
	uchar fnamecmp_type = FNAMECMP_FNAME;
	int ndx;

  read_loop:
	while (1) {
		ndx = read_ndx(f_in);

		if (ndx >= 0)
			break;
		if (ndx == NDX_DONE)
			return ndx;
		if (ndx == NDX_DEL_STATS) {
			read_del_stats(f_in);
			if (am_sender && am_server)
				write_del_stats(f_out);
			continue;
		}
		if (!inc_recurse || am_sender) {
			int last;
			if (first_flist)
				last = first_flist->prev->ndx_start + first_flist->prev->used - 1;
			else
				last = -1;
			rprintf(FERROR,
				"Invalid file index: %d (%d - %d) [%s]\n",
				ndx, NDX_DONE, last, who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}
		if (ndx == NDX_FLIST_EOF) {
			flist_eof = 1;
			if (DEBUG_GTE(FLIST, 3))
				rprintf(FINFO, "[%s] flist_eof=1\n", who_am_i());
			write_int(f_out, NDX_FLIST_EOF);
			continue;
		}
		ndx = NDX_FLIST_OFFSET - ndx;
		if (ndx < 0 || ndx >= dir_flist->used) {
			ndx = NDX_FLIST_OFFSET - ndx;
			rprintf(FERROR,
				"Invalid dir index: %d (%d - %d) [%s]\n",
				ndx, NDX_FLIST_OFFSET,
				NDX_FLIST_OFFSET - dir_flist->used + 1,
				who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}

		if (DEBUG_GTE(FLIST, 2)) {
			rprintf(FINFO, "[%s] receiving flist for dir %d\n",
				who_am_i(), ndx);
		}
		/* Send all the data we read for this flist to the generator. */
		start_flist_forward(ndx);
		flist = recv_file_list(f_in, ndx);
		flist->parent_ndx = ndx;
		stop_flist_forward();
	}

	iflags = protocol_version >= 29 ? read_shortint(f_in)
		   : ITEM_TRANSFER | ITEM_MISSING_DATA;

	/* Support the protocol-29 keep-alive style. */
	if (protocol_version < 30 && ndx == cur_flist->used && iflags == ITEM_IS_NEW) {
		if (am_sender)
			maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
		goto read_loop;
	}

	flist = flist_for_ndx(ndx, "read_ndx_and_attrs");
	if (flist != cur_flist) {
		cur_flist = flist;
		if (am_sender) {
			file_old_total = cur_flist->used;
			for (flist = first_flist; flist != cur_flist; flist = flist->next)
				file_old_total += flist->used;
		}
	}

	if (iflags & ITEM_BASIS_TYPE_FOLLOWS)
		fnamecmp_type = read_byte(f_in);
	*type_ptr = fnamecmp_type;

	if (iflags & ITEM_XNAME_FOLLOWS) {
        if (iflags & ITEM_XNAME_FOLLOWS) {
                if ((len = read_vstring(f_in, buf, MAXPATHLEN)) < 0)
                        exit_cleanup(RERR_PROTOCOL);
        } else {
                *buf = '\0';
                len = -1;
			rprintf(FERROR,
				"received request to transfer non-regular file: %d [%s]\n",
				ndx, who_am_i());
			exit_cleanup(RERR_PROTOCOL);
		}
	}

	*iflag_ptr = iflags;
	return ndx;
}


    string shortestBeautifulSubstring(string s, int k) {
        const auto& check = [&](int l1, int r1, int l2, int r2) {
            const int c1 = r1 - l1 + 1, c2 = r2 -l2 + 1;
            if (c1 > c2) {
                return false;
            }
            if (c1 < c2) {
                return true;
            }
            for (int i = 0; i < c1; ++i) {
                if (s[l1 + i] != s[l2 + i]) {
                    return s[l1 + i] < s[l2 + i];
                }
            }
            return false;
        };
        
        vector<int> result = {};
        for (int right = 0, left = 0, curr = 0; right < size(s); ++right) {
            curr += static_cast<int>(s[right] == '1');
            while (curr == k + 1) {
                curr -= static_cast<int>(s[left++] == '1');
            }
            while (left < size(s) && s[left] == '0') {
                ++left;
            }
            if (curr == k) {
                if (empty(result) || check(left, right, result[0], result[1])) {
                    result = {left, right};
                }
            }
        }
        return !empty(result) ? s.substr(result[0], result[1] - result[0] + 1) : "";
    }


