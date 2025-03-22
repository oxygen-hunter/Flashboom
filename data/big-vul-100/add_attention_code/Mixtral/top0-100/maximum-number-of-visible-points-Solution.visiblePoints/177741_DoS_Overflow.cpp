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

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        static const double PI = atan2(0, -1);

        vector<double> arr;
        int extra = 0;
        for (const auto& p : points) {
            if (p == location) {
                ++extra;
                continue;
            }
            arr.emplace_back(atan2(p[1] - location[1], p[0] - location[0]));
        }
        sort(begin(arr), end(arr));
        const int n = size(arr);
        for (int i = 0; i < n; ++i) {  // make it circular
            arr.emplace_back(arr[i] + 2.0 * PI);
        }
        const double d = 2.0 * PI * (angle / 360.0);
        int result = 0;
        for (int left = 0, right = 0; right < size(arr); ++right) {
            while (arr[right] - arr[left] > d) {
                ++left;
            }
            result = max(result, right - left + 1);
        }
        return result + extra;
    }

