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


    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        const auto& bfs = [&]() {
            vector<bool> lookup(n);
            lookup[k] = true;
            vector<int> q = {k};
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    for (const auto& v : adj[u]) {
                        if (lookup[v]) {
                            continue;
                        }
                        lookup[v] = true;
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return lookup;
        };
       
        for (const auto& e : invocations) {
            adj[e[0]].emplace_back(e[1]);
        }
        const auto& lookup = bfs();
        for (const auto& e : invocations) {
            if (lookup[e[0]] != lookup[e[1]]) {
                vector<int> result(n);
                iota(begin(result), end(result), 0);
                return result;
            }
        }
        vector<int> result;
        for (int u = 0; u < n; ++u) {
            if (!lookup[u]) {
                result.emplace_back(u);
            }
        }
        return result;
    }


