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


    TreeNode* findNeartestRightNode(TreeNode* root, TreeNode* u) {
        vector<TreeNode *> q = {root};
        while (!empty(q)) {
            vector<TreeNode *> new_q;
            for (int i = 0; i < size(q); ++i) {
                if (q[i] == u) {
                    return i + 1 < size(q) ? q[i + 1] : nullptr;
                }
                if (q[i]->left) {
                    new_q.emplace_back(q[i]->left);
                }
                if (q[i]->right) {
                    new_q.emplace_back(q[i]->right);
                }
            }
            q = move(new_q);
        }
        return nullptr;
    }


