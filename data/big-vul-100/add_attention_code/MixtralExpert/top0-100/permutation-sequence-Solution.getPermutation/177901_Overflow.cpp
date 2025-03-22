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


    string getPermutation(int n, int k) {
        vector<int> nums;
        int total = 1;
        for (int i = 1; i <= n; ++i) {
            nums.emplace_back(i);
            total *= i;
        }

        // Cantor Ordering:
        // Construct the k-th permutation with a list of n numbers
        // Idea: group all permutations according to their first number (so n groups, each of
        // (n - 1)! numbers), find the group where the k-th permutation belongs, remove the common
        // first number from the list and append it to the resulting string, and iteratively
        // construct the (((k - 1) % (n - 1)!) + 1)-th permutation with the remaining n-1 numbers
        int group = total;
        stringstream permutation;
        while (n > 0) {
            group /= n;
            int idx = (k - 1) / group;
            permutation << nums[idx];
            nums.erase(nums.begin() + idx);
            k = (k - 1) % group + 1;
            --n;
        }

        return permutation.str();
    }


