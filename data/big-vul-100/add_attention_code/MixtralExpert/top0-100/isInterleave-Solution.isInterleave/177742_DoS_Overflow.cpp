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


        bool isInterleave(string s1, string s2, string s3) {
            if(s1.length() + s2.length() != s3.length()) return false;

            if(s1.length() < s2.length()) return isInterleave(s2, s1, s3);

            vector<bool> f(s2.length() + 1, true);

            for(auto j = 1; j <= s2.length(); ++j) {
                f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
            }

            for(auto i = 1; i <= s1.length(); ++i) {
                f[0] = f[0] && s1[i - 1] == s3[i - 1];
                for(auto j = 1; j <= s2.length(); ++j) {
                    f[j] = (f[j] && s1[i - 1] == s3[i + j - 1])
                        || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
                }
            }

            return f[s2.length()];
        }


