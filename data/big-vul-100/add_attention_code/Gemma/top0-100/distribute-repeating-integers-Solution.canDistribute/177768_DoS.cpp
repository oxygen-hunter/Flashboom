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


    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> count;
        for(int i = 0; i < size(nums); ++i) {
            ++count[nums[i]];
        }
        int total = (1 << size(quantity)) - 1;
        vector<int> requirement(total + 1);
        for (int mask = 0; mask < size(requirement); ++mask) {  // Time: O(2^m)
            for (int i = 0; i < size(quantity); ++i) {  // Time: O(m)
                if (mask & (1 << i)) {
                    requirement[mask] += quantity[i];
                }
            }
        }
        vector<vector<int>> dp(2, vector<int>(total + 1));
        dp[0][0] = 1;
        int i = 0;
        vector<int> cnts;
        for (const auto& [_, cnt] : count) {
            cnts.emplace_back(cnt);
        }
        if (size(quantity) < size(cnts)) {  // at most use top m cnts
            nth_element(begin(cnts), begin(cnts) + size(quantity) - 1, end(cnts), greater<int>());
            cnts.resize(size(quantity));
        }
        for (int i = 0; i < size(cnts); ++i) {  // Time: O(m)
            dp[(i + 1) % 2] = vector<int>(total + 1);
            // submask enumeration:
            // => sum(nCr(m, k) * 2^k for k in xrange(m+1)) = (1 + 2)^m = 3^m
            // => Time: O(3^m), see https://cp-algorithms.com/algebra/all-submasks.html
            for (int mask = total; mask >= 0; --mask) {
                dp[(i + 1) % 2][mask] |= dp[i % 2][mask];
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    if (requirement[submask] <= cnts[i] && dp[i % 2][mask ^ submask]) {
                        dp[(i + 1) % 2][mask] = 1;
                    }
                }
            }
        }
        return dp[size(cnts) % 2][total];
    }


