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

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto& topological_sort = [&](const auto& conditions) {
            vector<vector<int>> adj(k);
            vector<int> in_degree(k);
            for (const auto& c : conditions) {
                const int u = c[0] - 1, v = c[1] - 1;
                adj[u].emplace_back(v);
                ++in_degree[v];
            }
            vector<int> result;
            vector<int> q;
            for (int u = 0; u < k; ++u) {
                if (!in_degree[u]) {
                    q.emplace_back(u);
                }
            }
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    result.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        --in_degree[v];
                        if (in_degree[v]) {
                            continue;
                        }
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        const auto& row_order = topological_sort(rowConditions);
        if (size(row_order) != k) {
            return {};
        }
        const auto& col_order = topological_sort(colConditions);
        if (size(col_order) != k) {
            return {};
        }
        vector<int> row_idx(k);
        for (int i = 0; i < k; ++i) {
            row_idx[row_order[i]] = i;
        }
        vector<int> col_idx(k);
        for (int i = 0; i < k; ++i) {
            col_idx[col_order[i]] = i;
        }
        vector<vector<int>> result(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            result[row_idx[i]][col_idx[i]] = i + 1;
        }
        return result;
    }

