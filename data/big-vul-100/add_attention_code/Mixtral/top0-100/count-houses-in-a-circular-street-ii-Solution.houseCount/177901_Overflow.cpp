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

    int houseCount(Street* street, int k) {
        while (!street->isDoorOpen()) {
            street->moveRight();
        }
        int result = 0;
        for (int i = 0; i <= k; ++i) {
            if (i && street->isDoorOpen()) {
                street->closeDoor();
                result = i;
            }
            street->moveRight();
        }
        return result;
    }

