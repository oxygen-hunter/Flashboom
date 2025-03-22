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

    int slidingPuzzle(vector<vector<int>>& board) {
        const auto& R = board.size(), &C = board[0].size();
        vector<int> begin, end;
        unordered_map<int, pair<int, int>> expected;
        int zero_idx = 0;
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                auto val = (C * i + j + 1) % (R * C);
                expected[val] = {i, j};
                if (board[i][j] == 0) {
                    zero_idx = begin.size();
                }
                begin.emplace_back(board[i][j]);
                end.emplace_back(val);
            }
        }
        vector<int> end_wrong(end);
        swap(end_wrong[end_wrong.size() - 2], end_wrong[end_wrong.size() - 3]);
           
        using P = tuple<int, int, int, vector<int>>;
        priority_queue<P, vector<P>, greater<P>> min_heap;
        min_heap.emplace(make_tuple(0, 0, zero_idx, begin));
        unordered_map<vector<int>, int, Hash<vector<int>>> lookup;
        lookup[begin] = 0;
        while (!min_heap.empty()) {
            int f, g, zero;
            vector<int> board;
            tie(f, g, zero, board) = min_heap.top(); min_heap.pop();
            if (board == end) {
                return g;
            }
            if (board == end_wrong) {
                return -1;
            }
            if (f > lookup[board]) {
                continue;
            }
            int r = zero / C;
            int c = zero % C;
            static const vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for (const auto& direction : directions) {
                int i = r + direction.first;
                int j = c + direction.second;
                if (0 <= i && i < R && 0 <= j && j < C) {
                    auto new_zero = C * i + j;
                    auto new_board = board;
                    swap(new_board[zero], new_board[new_zero]);
                    f = g + 1 + heuristic_estimate(new_board, R, C, expected);
                    if (!lookup.count(new_board) || f < lookup[new_board])
                        lookup[new_board] = f;
                        min_heap.emplace(make_tuple(f, g + 1, new_zero, new_board));
                    }
                }
            }
        }

