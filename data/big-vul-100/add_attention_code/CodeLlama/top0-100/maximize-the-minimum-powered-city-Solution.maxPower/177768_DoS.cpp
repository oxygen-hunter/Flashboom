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


    long long maxPower(vector<int>& stations, int r, int k) {
        const auto& min_power = [&]() {
            int64_t mn = numeric_limits<int64_t>::max();
            int64_t curr = accumulate(cbegin(stations), cbegin(stations) + r, 0ll);
            for (int i = 0; i < size(stations); ++i) {
                if (i + r < size(stations)) {
                    curr += stations[i + r];
                }
                if (i >= r + 1) {
                    curr -= stations[i - (r + 1)];
                }
                mn = min(mn, curr);
            }
            return mn;
        };

        const int64_t mn = min_power();
        const auto& check = [&](int64_t target) {
            vector<int> arr(cbegin(stations), cend(stations));
            int64_t curr = accumulate(cbegin(arr), cbegin(arr) + r, 0ll);
            int cnt = k;
            for (int i = 0; i < size(arr); ++i) {
                if (i + r < size(arr)) {
                    curr += arr[i + r];
                }
                if (i >= r + 1) {
                    curr -= arr[i - (r + 1)];
                }
                if (curr >= target) {
                    continue;
                }
                const auto diff = target - curr;
                if (diff > cnt) {
                    return false;
                }
                cnt -= diff;
                curr += diff;
                if (i + r < size(arr)) {
                    arr[i + r] += diff;
                }
            }
            return true;
        };

        int64_t left = mn, right = mn + k;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (!check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return right;
    }


