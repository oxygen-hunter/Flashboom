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

    int palindromePartition(string s, int k) {
        // dp1[i][j]: minimum number of changes to make s[i, j] palindrome
        vector<vector<int>> dp1(s.length(), vector<int>(s.length()));
        for (int l = 1; l <= s.length(); ++l) {
            for (int i = 0; i + l <= s.length(); ++i) {
                int j = i + l - 1;
                if (i == j - 1) {
                    dp1[i][j] = s[i] == s[j] ? 0 : 1;
                }  else if (i != j) {
                    dp1[i][j] = s[i] == s[j] ? dp1[i + 1][j - 1] : dp1[i + 1][j - 1] + 1;
                }
            }
        }
        // dp2[d][i]: minimum number of changes to divide s[0, i] into d palindromes
        vector<vector<int>> dp2(2, vector<int>(s.length(), numeric_limits<int>::max()));
        dp2[1] = dp1[0];
        for (int d = 2; d <= k; ++d) {
            dp2[d % 2] = vector<int>(s.length(), numeric_limits<int>::max());
            for (int i = d - 1; i < s.length(); ++i) {
                for (int j = d - 2; j < i; ++j) {
                    dp2[d % 2][i] = min(dp2[d % 2][i], dp2[(d - 1) % 2][j] + dp1[j + 1][i]);
                }
            }
        }
        return dp2[k % 2][s.length() - 1];
    }

