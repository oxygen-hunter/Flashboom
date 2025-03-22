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

    bool sumGame(string num) {
        // (1) if both halfs have '?',
        //     alice will optimally choose 9 or 0 from one half to maximize or minimize the diff of both half sums,
        //     and bob will optimally choose the same number from the other half to minimize or maximize the diff of both half sums.
        //     in the end, it turns that only one half has '?' and the diff of both half sums is still the same as original
        // (2) if smaller half has no '?', then alice wins
        // (3) if smaller half has '?'
        //     (3.1) if cnt of '?' is odd, alice can choose the last number to make the diff of both half sums != 0, then alice wins
        //     (3.2) if cnt of '?' is even
        //           (3.2.1) if larger-smaller = cnt/2 * 9, bob can always make a pair of sum 9 no matter what alice chooses, then bob wins
        //           (3.2.2) if larger-smaller > cnt/2 * 9, alice can always choose 0 no matter what bob chooses, then alice wins
        //           (3.2.3) if larger-smaller < cnt/2 * 9, alice can always choose 9 no matter what bob chooses, then alice wins
        int cnt = 0, total = 0;
        for (int i = 0; i < size(num); ++i) {
            if (num[i] == '?') {
                cnt += (i < size(num) / 2) ? -1 : 1;
            } else {
                total += (i < size(num) / 2) ? num[i] - '0' : -(num[i] - '0');
            }
        }
        return cnt % 2 ? true : total != cnt / 2 * 9;
    }

