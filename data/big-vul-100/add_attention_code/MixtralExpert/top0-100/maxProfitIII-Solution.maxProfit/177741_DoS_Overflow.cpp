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


        int maxProfit(vector<int> &prices) {
            const int n = prices.size();

            if(n < 2)
                return 0;

            vector<int> f(n, 0);
            vector<int> g(n, 0);

            for(int i = 1, valley = prices[0]; i < n; ++i) {
                f[i] = max(f[i - 1], prices[i] - valley);
                valley = min(valley, prices[i]);
            }

            for(int i = n - 2, peak = prices[n - 1]; i >= 0; --i) {
                g[i] = max(g[i + 1], peak - prices[i]);
                peak = max(peak, prices[i]);
            }

            int ans = 0;
            for(int i = 0; i < n; ++i) {
                ans = max(ans, f[i] + g[i]);
            }

            return ans;
        }


