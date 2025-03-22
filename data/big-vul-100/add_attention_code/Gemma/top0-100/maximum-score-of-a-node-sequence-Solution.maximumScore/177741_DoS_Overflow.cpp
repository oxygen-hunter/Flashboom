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


    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        using PII = pair<int, int>;
        using Heap = vector<PII>;
        const auto& find_top3 = [&scores](const auto& x, Heap *top3) {            
            top3->emplace_back(scores[x], x); push_heap(begin(*top3), end(*top3), greater<PII>());
            if (size(*top3) > 3) {
                pop_heap(begin(*top3), end(*top3), greater<PII>()); top3->pop_back();
            }
        };
        vector<Heap> top3(size(scores));
        for (const auto& e : edges) {
            find_top3(e[1], &top3[e[0]]);
            find_top3(e[0], &top3[e[1]]);
        }
        int result = -1;
        for (const auto& e : edges) {
            const int a = e[0], b = e[1];
            for (const auto& [_, c] : top3[a]) {
                if (c == b) {
                    continue;
                }
                for (const auto& [_, d] : top3[b]) {
                    if (d == a || d == c) {
                        continue;
                    }
                    result = max(result, scores[a] + scores[b] + scores[c] + scores[d]);
                }
            }
        }
        return result;
    }


