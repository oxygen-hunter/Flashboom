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

    long long maximumScore(vector<vector<int>>& grid) {
        vector<int64_t> prefix(size(grid)+ 1);
        for (int i = 0; i < size(grid); ++i) {
            prefix[i + 1] = prefix[i] + grid[i][0];
        }
        // dp[0][i]: the maximum score from 0 to the current column, and the current column has i black cells, without scoring the white cells of the current column
        // dp[1][i]: the maximum score from 0 to the current column, and the current column has i black cells, with scoring the white cells of the current column
        vector<vector<int64_t>> dp(2, vector<int64_t>(size(grid) + 1));
        for (int j = 1; j < size(grid[0]); ++j) {
            vector<int64_t> new_prefix(size(grid)+ 1);
            for (int i = 0; i < size(grid); ++i) {
                new_prefix[i + 1] = new_prefix[i] + grid[i][j];
            }
            vector<vector<int64_t>> new_dp(2, vector<int64_t>(size(grid) + 1));
            for (int i = 0; i <= size(grid); ++i) {
                for (int k = 0; k <= size(grid); ++k) {
                    new_dp[0][i] = max(new_dp[0][i], max(prefix[i] - prefix[k], static_cast<int64_t>(0)) + dp[0][k]);
                    new_dp[1][i] = max(new_dp[1][i], dp[1][k] + max(new_prefix[k] - new_prefix[i], static_cast<int64_t>(0)));
                }
                new_dp[0][i] = max(new_dp[0][i], ranges::max(dp[1]));
                new_dp[1][i] = max(new_dp[1][i], new_dp[0][i]);
            }
            dp = move(new_dp);
            prefix = move(new_prefix);
        }
        return ranges::max(dp[1]);
    }

