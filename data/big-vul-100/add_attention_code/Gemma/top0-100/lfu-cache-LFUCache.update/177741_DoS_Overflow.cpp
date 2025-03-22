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


    void update(int key, int value) {
        int freq = 0;
        if (key_to_nodeit_.count(key)) {
            auto old_node = *key_to_nodeit_[key];        
            freq = std::get<FREQ>(old_node);
            freq_to_nodes_[freq].erase(key_to_nodeit_[key]);
            if (freq_to_nodes_[freq].empty()) {
                freq_to_nodes_.erase(freq);
                if (min_freq_ == freq) {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = min(min_freq_, ++freq);
        freq_to_nodes_[freq].emplace_back(key, value, freq);
        key_to_nodeit_[key] = prev(freq_to_nodes_[freq].end());
        ++size_;
    }


