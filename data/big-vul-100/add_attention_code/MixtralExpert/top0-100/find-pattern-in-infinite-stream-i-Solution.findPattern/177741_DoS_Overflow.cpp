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


    int findPattern(InfiniteStream* stream, vector<int>& pattern) {
        const auto& getPrefix = [](const auto& pattern) {
            vector<int> prefix(size(pattern), -1);
            int j = -1;
            for (int i = 1; i < size(pattern); ++i) {
                while (j > -1 && pattern[j + 1] != pattern[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == pattern[i]) {
                    ++j;
                }
                prefix[i] = j;
            }
            return prefix;
        };

        vector<int> result;
        const vector<int> prefix = getPrefix(pattern);
        int j = -1;
        for (int i = 0; ; ++i) {
            const auto d = stream->next();
            while (j > -1 && pattern[j + 1] != d) {
                j = prefix[j];
            }
            if (pattern[j + 1] == d) {
                ++j;
            }
            if (j == size(pattern) - 1) {
                return i - j;
            }
        }
        return -1;
    }


