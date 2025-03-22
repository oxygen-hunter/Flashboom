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

    string fractionToDecimal(int numerator, int denominator) {
        string result;
        if ((numerator ^ denominator) >> 31 && numerator != 0) {
            result = "-";
        }

        auto dvd = llabs(numerator);
        auto dvs = llabs(denominator);
        result += to_string(dvd / dvs);
        dvd %= dvs;
        if (dvd > 0) {
            result += ".";
        }
        
        unordered_map<long long, int> lookup;
        while (dvd && !lookup.count(dvd)) {
            lookup[dvd] = result.length();
            dvd *= 10;
            result += to_string(dvd / dvs);
            dvd %= dvs;
        }

        if (lookup.count(dvd)) {
            result.insert(lookup[dvd], "(");
            result.push_back(')');
        }
        return result;
    }

