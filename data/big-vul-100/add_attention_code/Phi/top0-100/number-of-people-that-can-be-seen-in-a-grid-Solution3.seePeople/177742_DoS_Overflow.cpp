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

    vector<vector<int>> seePeople(vector<vector<int>>& heights) {
        vector<vector<int>> result(size(heights), vector<int>(size(heights[0])));
        const auto& count = [](const auto& height, int i, vector<int> *stk, const auto& increase) {
            while (!empty(*stk) && height(stk->back()) < height(i)) {
                increase(stk->back()); stk->pop_back();
            }
            if (!empty(*stk)) {
                increase(stk->back());
            }
            if (!empty(*stk) && height(stk->back()) == height(i)) {
                stk->pop_back();
            }
            stk->emplace_back(i);
        };

        for (int i = 0; i < size(heights); ++i) {
            const auto& height = [&](int x) {
                return heights[i][x];
            };
            const auto& increase = [&](int x) {
                ++result[i][x];
            };
            vector<int> stk;
            for (int j = 0; j < size(heights[0]); ++j) {
                count(height, j, &stk, increase);
            }
        }
        for (int j = 0; j < size(heights[0]); ++j) {
            const auto& height = [&](int x) {
                return heights[x][j];
            };
            const auto& increase = [&](int x) {
                ++result[x][j];
            };
            vector<int> stk;
            for (int i = 0; i < size(heights); ++i) {
                count(height, i, &stk, increase);
            }
        }
        return result;
    }

