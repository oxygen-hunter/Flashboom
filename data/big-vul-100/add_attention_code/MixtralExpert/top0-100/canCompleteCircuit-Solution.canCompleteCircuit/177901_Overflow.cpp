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


        int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
            int total = 0;
            int sum = 0;
            int j = -1;

            for(int i = 0; i < gas.size(); ++i) {
                total += gas[i] - cost[i];
                sum += gas[i] - cost[i];
                if(sum < 0) { // find the gas station which should be the last one
                    sum = 0;
                    j = i;
                }
            }

            return (total >= 0) ? j + 1 : -1;
        }


