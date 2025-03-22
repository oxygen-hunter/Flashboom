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

    int minAbsDifference(vector<int>& nums, int goal) {
        int mx = 0, mn = 0;
        for (const auto& x : nums) {
            if (x > 0) {
                mx += x;
            } else if (x < 0) {
                mn += x;
            }
        }
        if (goal > mx) {
            return goal - mx;
        }
        if (goal < mn) {
            return mn - goal;
        }
        int result = abs(goal);
        unordered_set<int> sums1{0};
        for (auto i = 0; i < size(nums) / 2; ++i) {
            for (const auto& x : vector<int>(cbegin(sums1), cend(sums1))) {
                if (!sums1.emplace(x + nums[i]).second) {
                    continue;
                }
                result = min(result, abs(goal - x - nums[i]));  // case of right half part is 0
            }
        }
        vector<int> sorted_sums1(cbegin(sums1), cend(sums1));  // Space: O(2^(n/2))
        sort(begin(sorted_sums1), end(sorted_sums1));  // Time: O((n/2) * 2^(n/2)) = O(n * 2^(n/2))
        unordered_set<int> sums2{0};
        for (int i = size(nums) / 2; i < size(nums); ++i) {
            for (const auto& x : vector<int>(cbegin(sums2), cend(sums2))) {
                if (!sums2.emplace(x + nums[i]).second) {
                    continue;
                }
                auto cit = lower_bound(cbegin(sorted_sums1), cend(sorted_sums1), goal - x - nums[i]);  // Time: O(2^(n/2)) * O(n/2)
                if (cit != cend(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *cit));
                }
                if (cit != cbegin(sorted_sums1)) {
                    result = min(result, abs(goal - x - nums[i] - *prev(cit)));
                }
                if (result == 0) {
                    return result;
                }
            }
        }
        return result;
    }

