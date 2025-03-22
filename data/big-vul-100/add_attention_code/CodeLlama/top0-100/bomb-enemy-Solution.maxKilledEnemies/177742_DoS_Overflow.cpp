gnutls_session_get_data (gnutls_session_t session,
                         void *session_data, size_t * session_data_size)
{

  gnutls_datum_t psession;
  int ret;

  if (session->internals.resumable == RESUME_FALSE)
    return GNUTLS_E_INVALID_SESSION;

  psession.data = session_data;

  ret = _gnutls_session_pack (session, &psession);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }
 
   if (psession.size > *session_data_size)
     {
       ret = GNUTLS_E_SHORT_MEMORY_BUFFER;
       goto error;
     }

  if (session_data != NULL)
    memcpy (session_data, psession.data, psession.size);

  ret = 0;

error:
  _gnutls_free_datum (&psession);
  return ret;
}


    int maxKilledEnemies(vector<vector<char>>& grid) {
        int result = 0;
        if (grid.empty() || grid[0].empty()) {
            return result;
        }

        vector<vector<int>> down{grid.size(), vector<int>(grid[0].size())};
        vector<vector<int>> right{grid.size(), vector<int>(grid[0].size())};
        for (int i = grid.size() - 1; i >= 0; --i) {
            for (int j = grid[0].size() - 1; j >= 0; --j) {
                if (grid[i][j] != 'W') {
                    if (i + 1 < grid.size()) {
                        down[i][j] = down[i + 1][j];
                    }
                    if (j + 1 < grid[0].size()) {
                        right[i][j] = right[i][j + 1];
                    }
                    if (grid[i][j] == 'E') {
                        ++down[i][j];
                        ++right[i][j];
                    }
                }
            }
        }

        int left = 0;
        vector<int> up(grid[0].size());
        for (int i = 0; i < grid.size(); ++i) {
            left = 0;
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] == 'W') {
                    up[j] = 0;
                    left = 0;
                } else if (grid[i][j] == 'E') {
                    ++up[j];
                    ++left;
                } else {
                    result = max(result, left + up[j] + right[i][j] + down[i][j]);
                }
            }
        }

        return result;
    }


