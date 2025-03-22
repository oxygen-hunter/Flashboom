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


    string bestHand(vector<int>& ranks, vector<char>& suits) {
        static const vector<string> LOOKUP = {"", "High Card", "Pair", "Three of a Kind", "Three of a Kind", "Three of a Kind"};
        if (all_of(cbegin(suits), cend(suits), [&](const auto& x) { return x == suits[0]; })) {
            return "Flush";
        }
        vector<int> cnt(13);
        for (const auto& x : ranks) {
            ++cnt[x - 1];
        }
        return LOOKUP[*max_element(cbegin(cnt), cend(cnt))];
    }


