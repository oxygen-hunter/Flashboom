_asn1_ltostr (long v, char *str)
 {
   long d, r;
   char temp[LTOSTR_MAX_SIZE];
  int count, k, start;

  if (v < 0)
    {
      str[0] = '-';
      start = 1;
      v = -v;
    }
  else
    start = 0;

  count = 0;
  do
    {
      d = v / 10;
      r = v - d * 10;
      temp[start + count] = '0' + (char) r;
       count++;
       v = d;
     }
  while (v);
 
   for (k = 0; k < count; k++)
     str[k + start] = temp[start + count - k - 1];
  str[count + start] = 0;
  return str;
}


    long long minimumPerimeter(long long neededApples) {
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        // 2r-1,                 r-1,                  2r-1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // r   ,  r-1, ...,   1, 0  ,   1, ...,   r-1, r
        // r+1 ,    r, ...,   2, 1  ,   2, ...,   r  , r+1
        // .                     .                     .    
        // .                     .                     .    
        // .                     .                     .    
        // 2r-1,                 r-1,                  2r-1
        // 2r  , 2r-1, ..., r+1, r  , r+1, ..., 2*r-1, 2*r
        //
        // the sum of each row/col forms an arithmetic sequence
        // => let ai = (((r + (r-1) + ... + r + 0) + (0 + 1 + 2 + ... + r)) - 0) + i*(2r+1)
        //           = (2*(0+r)*(r+1)/2-0) + i*(2r+1)
        //           = r*(r+1) + i*(2r+1)
        // => total  = 2*(a0 + a1 + ... ar) - a0
        //           = 2*(r*(r+1) + r*(r+1) + r*(2r+1)))*(r+1)/2 - r*(r+1)
        //           = r*(4r+3)*(r+1)-r*(r+1)
        //           = 4r^3+6r^2+2r
        // => find min r, s.t. 4r^3+6r^2+2r >= neededApples

        int64_t left = 1, right = pow(neededApples / 4.0, 1.0 / 3);
        while (left <= right) {
            const auto& mid = left + (right - left) / 2;
            if (check(neededApples, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return 8 * left;
    }


