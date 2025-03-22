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

    int maxTrailingZeros(vector<vector<int>>& grid) {
        const auto& factor = [](int x) {
            static const array<int, 2> primes = {2, 5};
            array<int, 2> cnt = {0, 0};
            for (int i = 0; i < size(primes); ++i) {
                while (x && x % primes[i] == 0) {
                    x /= primes[i];
                    ++cnt[i];
                }
            }
            return cnt;
        };
        const auto& add = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] + b[0], a[1] + b[1]};
        };
        const auto& sub = [](const auto& a, const auto& b) {
            return array<int, 2>{a[0] - b[0], a[1] - b[1]};
        };
        const auto& count = [](const auto& a) {
            return min(a[0], a[1]);
        };

        vector<vector<array<int, 2>>> left(size(grid), vector<array<int, 2>>(size(grid[0])));
        for (int i = 0; i < size(grid); ++i) {
            left[i][0] = factor(grid[i][0]);
            for (int j = 1; j < size(grid[0]); ++j) {
                left[i][j] = add(left[i][j - 1], factor(grid[i][j]));
            }
        }
        int result = 0;
        for (int j = 0; j < size(grid[0]); ++j) {
            array<int, 2> total = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                total = add(total, factor(grid[i][j]));
            }
            array<int, 2> up = {0, 0};
            for (int i = 0; i < size(grid); ++i) {
                const auto& right = j ? sub(left[i].back(), left[i][j - 1]) : left[i].back();
                result = max({result, count(add(left[i][j], up)), count(add(right, up))});
                up = add(up, factor(grid[i][j]));
                const auto& down = sub(total, up);
                result = max({result, count(add(left[i][j], down)), count(add(right, down))});
            }
        }
        return result;
    }

