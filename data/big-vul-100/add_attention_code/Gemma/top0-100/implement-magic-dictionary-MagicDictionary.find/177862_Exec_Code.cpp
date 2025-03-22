restore_page_device(const gs_gstate * pgs_old, const gs_gstate * pgs_new)
 {
     gx_device *dev_old = gs_currentdevice(pgs_old);
     gx_device *dev_new;
    gx_device *dev_t1;
     gx_device *dev_t2;
     bool samepagedevice = obj_eq(dev_old->memory, &gs_int_gstate(pgs_old)->pagedevice,
         &gs_int_gstate(pgs_new)->pagedevice);
 
     if ((dev_t1 = (*dev_proc(dev_old, get_page_device)) (dev_old)) == 0)
        return false;
     /* If we are going to putdeviceparams in a callout, we need to */
     /* unlock temporarily.  The device will be re-locked as needed */
     /* by putdeviceparams from the pgs_old->pagedevice dict state. */
        dev_old->LockSafetyParams = false;
    dev_new = gs_currentdevice(pgs_new);
     dev_new = gs_currentdevice(pgs_new);
     if (dev_old != dev_new) {
         if ((dev_t2 = (*dev_proc(dev_new, get_page_device)) (dev_new)) == 0)
            return false;
        if (dev_t1 != dev_t2)
            return true;
     }
     /*
      * The current implementation of setpagedevice just sets new
      * parameters in the same device object, so we have to check
      * whether the page device dictionaries are the same.
      */
    return !samepagedevice;
 }


    bool find(const string& word, TrieNode *curr, int i, bool mistakeAllowed) {
        if (i == word.length()) {
            return curr->isString && !mistakeAllowed; 
        }

        if (!curr->leaves.count(word[i])) {
            return mistakeAllowed ?
                       any_of(curr->leaves.begin(), curr->leaves.end(),
                              [&](const pair<char, TrieNode *>& kvp) { 
                                  return find(word, kvp.second, i + 1, false);
                               }) :
                       false;
        }
                    
        if (mistakeAllowed) {
            return find(word, curr->leaves[word[i]], i + 1, true) ||
                   any_of(curr->leaves.begin(), curr->leaves.end(),
                          [&](const pair<char, TrieNode *>& kvp) { 
                              return kvp.first != word[i] && find(word, kvp.second, i + 1, false);
                          });
        }
        return find(word, curr->leaves[word[i]], i + 1, false);
    }


