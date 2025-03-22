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


    int shortestPathLength(vector<vector<int>>& graph) {
        static const auto& INF = numeric_limits<int>::max();
        vector<vector<int>> dp(1 << graph.size(),
                               vector<int>(graph.size(), INF));
        queue<pair<int, int>> q;
        for (int i = 0; i < graph.size(); ++i) {
            dp[1 << i][i] = 0;
            q.emplace(1 << i, i);
        }
        while (!q.empty()) {
            int state, node;
            tie(state, node) = q.front(); q.pop();
            auto steps = dp[state][node];
            for (const auto& nei : graph[node]) {
                auto new_state = state | (1 << nei);								
                if (dp[new_state][nei] == INF) {
                    dp[new_state][nei] = steps + 1;
                    q.emplace(new_state, nei);
                }
            }
        }
        return *min_element(dp.back().cbegin(), dp.back().cend());
    }


