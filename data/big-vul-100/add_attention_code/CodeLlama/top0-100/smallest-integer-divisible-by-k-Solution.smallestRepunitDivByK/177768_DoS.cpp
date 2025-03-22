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


    int smallestRepunitDivByK(int K) {
        // by observation, K % 2 = 0 or K % 5 = 0, it is impossible
        if (K % 2 == 0 || K % 5 == 0) {
            return -1;
        }
        // let f(N) is a N-length integer only containing digit 1
        // given K % 2 != 0 and K % 5 != 0
        // if there is no N in range (1..K) s.t. f(N) % K = 0
        // => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
        // => due to pigeonhole principle, there must be at least 2 same remainders
        // => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
        // => (f(x) - f(y)) % K = 0
        // => (f(x-y) * 10^y) % K = 0
        // => due to (x-y) in range (1..K)
        // => f(x-y) % K != 0
        // => 10^y % K = 0
        // => K % 2 = 0 or K % 5 = 0
        // => -><-
        // it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
        int result = 0;
        for (int N = 1; N <= K; ++N) {
            result = (result * 10 + 1) % K;
            if (!result) {
                return N;
            }
        }
        assert(false);
        return -1;  // never reach
    }


