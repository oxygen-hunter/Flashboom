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

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        const auto& KMP = [](const auto& text, const auto& pattern) {
            const auto& getPrefix = [](const auto& pattern) {
                vector<int> prefix(size(pattern), -1);
                int j = -1;
                for (int i = 1; i < size(pattern); ++i) {
                    while (j != -1 && pattern[j + 1] != pattern[i]) {
                        j = prefix[j];
                    }
                    if (pattern[j + 1] == pattern[i]) {
                        ++j;
                    }
                    prefix[i] = j;
                }
                return prefix;
            };

            int result = 0;
            const vector<int> prefix = getPrefix(pattern);
            int j = -1;
            for (int i = 0; i < size(text); ++i) {
                while (j > -1 && pattern[j + 1] != text[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == text[i]) {
                    ++j;
                }
                if (j == size(pattern) - 1) {
                    ++result;
                    j = prefix[j];
                }
            }
            return result;
        };
    
        for (int i = 0; i + 1 < size(nums); ++i) {
            if (nums[i + 1] > nums[i]) {
                nums[i] = 1;
            } else if (nums[i + 1] < nums[i]) {
                nums[i] = -1;
            } else {
                nums[i] = 0;
            }
        }
        return KMP(nums, pattern);
    }

