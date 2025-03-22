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


    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        const auto& check = [&](int i, int j) {
            for (int ni = i - 1; ni <= i; ++ni) {
                for (int nj = j - 1; nj <= j + 1; ++nj) {
                    if (abs(image[ni][nj] - image[ni + 1][nj]) > threshold) {
                        return false;
                    }
                }
            }
            for (int ni = i - 1; ni <= i + 1; ++ni) {
                for (int nj = j - 1; nj <= j; ++nj) {
                    if (abs(image[ni][nj] - image[ni][nj + 1]) > threshold) {
                        return false;
                    }
                }
            }
            return true;
        };
    
        vector<vector<int>> result(size(image), vector<int>(size(image[0])));
        vector<vector<int>> cnt(size(image), vector<int>(size(image[0])));
        for (int i = 1; i + 1 < size(image); ++i) {
            for (int j = 1; j + 1 < size(image[0]); ++j) {
                if (!check(i, j)) {
                    continue;
                }
                int total = 0;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        total += image[ni][nj];
                    }
                }
                total /= 9;
                for (int ni = i - 1; ni <= i + 1; ++ni) {
                    for (int nj = j - 1; nj <= j + 1; ++nj) {
                        ++cnt[ni][nj];
                        result[ni][nj] += total;
                    }
                }
            }
        }
        for (int i = 0; i < size(image); ++i) {
            for (int j = 0; j < size(image[0]); ++j) {
                if (cnt[i][j]) {
                    result[i][j] /= cnt[i][j];
                } else {
                    result[i][j] = image[i][j];
                }
            }
        }
        return result;
    }


