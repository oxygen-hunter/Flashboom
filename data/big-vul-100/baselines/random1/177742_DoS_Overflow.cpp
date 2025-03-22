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


    int countTriplets(vector<int>& arr) {
        unordered_map<int, pair<int, int>> count_sum;
        count_sum[0] = {1, 0};
        int result = 0;
        for (int i = 0, prefix = 0; i < arr.size(); ++i) {
            prefix ^= arr[i];
            auto& [c, t] = count_sum[prefix];
            result += c * i - t;
            ++c, t += i + 1;
        }
        return result;
    }


