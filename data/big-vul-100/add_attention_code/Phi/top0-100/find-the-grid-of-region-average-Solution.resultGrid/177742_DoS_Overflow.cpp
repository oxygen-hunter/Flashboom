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

