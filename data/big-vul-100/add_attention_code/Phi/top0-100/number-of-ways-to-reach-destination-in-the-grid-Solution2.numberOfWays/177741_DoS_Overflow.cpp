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
  *session_data_size = psession.size;
 
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

    int numberOfWays(int n, int m, int k, vector<int>& source, vector<int>& dest) {
        static const int MOD = 1e9 + 7;
    
        int both_same = 0, row_same = 0, col_same = 0, no_same = 0;
        if (source == dest) {
            both_same = 1;
        } else if (source[0] == dest[0]) {
            row_same = 1;
        } else if (source[1] == dest[1]) {
            col_same = 1;
        } else {
            no_same = 1;
        }
        for (int _ = 0; _ < k; ++_) {
            tie(both_same, row_same, col_same, no_same) = tuple(
                (row_same + col_same) % MOD,
                (both_same * static_cast<int64_t>(m - 1) + row_same * static_cast<int64_t>(m - 2) + no_same) % MOD,
                (both_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(n - 2) + no_same) % MOD,
                (row_same * static_cast<int64_t>(n - 1) + col_same * static_cast<int64_t>(m - 1) + no_same * static_cast<int64_t>((n - 2) + (m - 2))) % MOD
            );
        }
        return both_same;
    }

