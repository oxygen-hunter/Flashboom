sparse_dump_region (struct tar_sparse_file *file, size_t i)
{
  union block *blk;
  off_t bytes_left = file->stat_info->sparse_map[i].numbytes;

  if (!lseek_or_error (file, file->stat_info->sparse_map[i].offset))
    return false;

  while (bytes_left > 0)
    {
      size_t bufsize = (bytes_left > BLOCKSIZE) ? BLOCKSIZE : bytes_left;
      size_t bytes_read;

      blk = find_next_block ();
      bytes_read = safe_read (file->fd, blk->buffer, bufsize);
      if (bytes_read == SAFE_READ_ERROR)
	{
          read_diag_details (file->stat_info->orig_file_name,
	                     (file->stat_info->sparse_map[i].offset
			      + file->stat_info->sparse_map[i].numbytes
			      - bytes_left),
 			     bufsize);
 	  return false;
 	}
 
       memset (blk->buffer + bytes_read, 0, BLOCKSIZE - bytes_read);
       bytes_left -= bytes_read;
    {
      size_t count;
      size_t wrbytes = (write_size > BLOCKSIZE) ? BLOCKSIZE : write_size;
      union block *blk = find_next_block ();
      if (!blk)
	{
	  ERROR ((0, 0, _("Unexpected EOF in archive")));
	  return false;
	}
      set_next_block_after (blk);
      count = blocking_write (file->fd, blk->buffer, wrbytes);
      write_size -= count;
      file->dumped_size += count;
      mv_size_left (file->stat_info->archive_file_size - file->dumped_size);
      file->offset += count;
      if (count != wrbytes)
	{
	  write_error_details (file->stat_info->orig_file_name,
			       count, wrbytes);
	  return false;
	}
    }
  return true;
}



/* Interface functions */
enum dump_status
sparse_dump_file (int fd, struct tar_stat_info *st)
{
 	  return false;
 	}
       set_next_block_after (blk);
       count = blocking_write (file->fd, blk->buffer, wrbytes);
       write_size -= count;
      file->dumped_size += count;
       mv_size_left (file->stat_info->archive_file_size - file->dumped_size);
       file->offset += count;
       if (count != wrbytes)

  rc = sparse_scan_file (&file);
  if (rc && file.optab->dump_region)
    {
      tar_sparse_dump_header (&file);

      if (fd >= 0)
	{
	  size_t i;

	  mv_begin_write (file.stat_info->file_name,
		          file.stat_info->stat.st_size,
		          file.stat_info->archive_file_size - file.dumped_size);
	  for (i = 0; rc && i < file.stat_info->sparse_map_avail; i++)
	    rc = tar_sparse_dump_region (&file, i);
	}
    }

  pad_archive (file.stat_info->archive_file_size - file.dumped_size);
  return (tar_sparse_done (&file) && rc) ? dump_status_ok : dump_status_short;
}

    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        static const auto& choice_mask =
            [](const auto& nums, const auto& idxs) {
                return accumulate(cbegin(idxs), cend(idxs), 0,
                                  [&nums](const auto& a, const auto& b) {
                                      return a | (1 << nums[b]);
                                  });
            };
        static const auto& next_pos =
            [](const auto& n, const auto& r, const auto& idxs) {
                int i = r - 1;
                for (; i >= 0; --i) {
                    if (idxs[i] != i + n - r) {
                        break;
                    }
                }
                return i;
            };

        vector<int> reqs(n);
        for (const auto& d : dependencies) {
            reqs[d[1] - 1] |= 1 << (d[0] - 1);
        }
        vector<int> dp(1 << n, n);
        dp[0] = 0;
        for (int mask = 0; mask < dp.size(); ++mask) {
            vector<int> candidates;
            for (int v = 0; v < n; ++v) {
                if ((mask & (1 << v)) == 0 && (mask & reqs[v]) == reqs[v]) {
                    candidates.emplace_back(v);
                }
            }
            const auto r = min(int(candidates.size()), k);
            vector<int> idxs(r);
            iota(begin(idxs), end(idxs), 0);
            const auto& new_mask = (mask | choice_mask(candidates, idxs));
            dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            for (int i; (i = next_pos(candidates.size(), r, idxs)) >= 0;) {
                ++idxs[i];
                for (int j = i + 1; j < k; ++j) {
                    idxs[j] = idxs[j - 1] + 1;
                }
                const auto& new_mask = (mask | choice_mask(candidates, idxs));
                dp[new_mask] = min(dp[new_mask], dp[mask] + 1);
            }
        }
        return dp.back();
    }

