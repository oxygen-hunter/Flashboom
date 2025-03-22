BufCompressedFill (BufFilePtr f)
{
    CompressedFile  *file;
    register char_type *stackp, *de_stack;
    register char_type finchar;
    register code_int code, oldcode, incode;
    BufChar	    *buf, *bufend;

    file = (CompressedFile *) f->private;

    buf = f->buffer;
    bufend = buf + BUFFILESIZE;
    stackp = file->stackp;
    de_stack = file->de_stack;
    finchar = file->finchar;
    oldcode = file->oldcode;
    while (buf < bufend) {
	while (stackp > de_stack && buf < bufend)
	    *buf++ = *--stackp;

	if (buf == bufend)
	    break;

	if (oldcode == -1)
	    break;

	code = getcode (file);
	if (code == -1)
	    break;
    
    	if ( (code == CLEAR) && file->block_compress ) {
	    for ( code = 255; code >= 0; code-- )
	    	file->tab_prefix[code] = 0;
	    file->clear_flg = 1;
	    file->free_ent = FIRST - 1;
	    if ( (code = getcode (file)) == -1 )	/* O, untimely death! */
	    	break;
    	}
    	incode = code;
    	/*
     	 * Special case for KwKwK string.
     	 */
    	if ( code >= file->free_ent ) {
	    *stackp++ = finchar;
	    code = oldcode;
    	}
    
    	/*
     	 * Generate output characters in reverse order
      	 */
     	while ( code >= 256 )
     	{
 	    *stackp++ = file->tab_suffix[code];
 	    code = file->tab_prefix[code];
     	}
    
    	/*
     	 * Generate the new entry.
     	 */
    	if ( (code=file->free_ent) < file->maxmaxcode ) {
	    file->tab_prefix[code] = (unsigned short)oldcode;
	    file->tab_suffix[code] = finchar;
	    file->free_ent = code+1;
    	} 
	/*
	 * Remember previous code.
	 */
	oldcode = incode;
    }
    file->oldcode = oldcode;
    file->stackp = stackp;
    file->finchar = finchar;
    if (buf == f->buffer) {
	f->left = 0;
	return BUFFILEEOF;
    }
    f->bufp = f->buffer + 1;
    f->left = (buf - f->buffer) - 1;
    return f->buffer[0];
}


    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        vector<int> lookup(size(nums), -1);
        for (int i = size(changeIndices) - 1; i >= 0; --i) {
            if (nums[changeIndices[i] - 1]) {
                lookup[changeIndices[i] - 1] = i;
            }
        }
        const int64_t total = accumulate(cbegin(nums), cend(nums), 0ll) + size(nums);
        const auto& check = [&](int t) {
            priority_queue<int, vector<int>, greater<int>> min_heap;
            int64_t total2 = 0, cnt = 0;
            for (int i = t - 1; i >= 0; --i) {
                if (i != lookup[changeIndices[i] - 1]) {
                    ++cnt;
                    continue;
                }
                min_heap.emplace(nums[changeIndices[i] - 1]);
                total2 += nums[changeIndices[i] - 1];
                if (cnt) {
                    --cnt;
                } else {
                    ++cnt;
                    total2 -= min_heap.top(); min_heap.pop();
                }
            }
            return total - (total2 + (size(min_heap))) <= cnt;
        };
    
        int64_t total2 = 0;
        for (int i = 0; i < size(nums); ++i) {
            total2 += lookup[i] != -1 ? 1 : nums[i];
        }
        int64_t left = total2 + size(nums), right = size(changeIndices);
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left <= size(changeIndices) ? left : -1;
    }


