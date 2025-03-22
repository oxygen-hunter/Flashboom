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

    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        const auto& check = [&](const auto& s1, const auto& s2) {
            if (size(s1) != size(s2)) {
                return false;
            }
            int cnt = 0;
            for (int k = 0; k < size(s1); ++k) {
                cnt += s1[k] != s2[k] ? 1 : 0;
                if (cnt == 2) {
                    return false;
                }
            }
            return cnt == 1;
        };

        vector<vector<int>> dp(n);
        for (int i = 0; i < n; ++i) {
            const auto& si = words[i];
            int mx_j = -1;
            for (int j = 0; j < i; ++j) {
                if (groups[i] != groups[j] && check(words[j], si) && (mx_j == -1 || size(dp[mx_j]) < size(dp[j]))) {
                    mx_j = j;
                }
            }
            if (mx_j != -1) {
                dp[i] = dp[mx_j];
            }
            dp[i].emplace_back(i);
        }
        
        const auto& ans = *max_element(cbegin(dp), cend(dp), [](const auto& a, const auto& b) {
            return size(a) < size(b);
        });
        vector<string> result;
        for (const auto& i : ans) {
            result.emplace_back(words[i]);
        }
        return result;
    }

