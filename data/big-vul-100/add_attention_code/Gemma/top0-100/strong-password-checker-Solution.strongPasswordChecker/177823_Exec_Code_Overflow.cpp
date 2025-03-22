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


    int strongPasswordChecker(string s) {
        int missing_type_cnt = 3;
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isdigit(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return isupper(c); }));
        missing_type_cnt -= static_cast<int>(any_of(s.begin(), s.end(), [](char c){ return islower(c); }));

        int total_change_cnt = 0;
        int one_change_cnt = 0, two_change_cnt = 0, three_change_cnt = 0;
        for (int i = 2; i < s.length();) {
            if (s[i] == s[i - 1] && s[i - 1] == s[i - 2]) {
                int length = 2;
                while (i < s.length() && s[i] == s[i - 1]) {
                    ++length;
                    ++i;
                }
                total_change_cnt += length / 3;
                if (length % 3 == 0) {
                    ++one_change_cnt;
                } else if (length % 3 == 1) {
                    ++two_change_cnt;
                } else {
                    ++three_change_cnt;
                }
            } else {
                ++i;
            }
        }

        if (s.length() < 6) {
            return max(missing_type_cnt, 6 - static_cast<int>(s.length()));
        } else if (s.length() <= 20) {
            return max(missing_type_cnt, total_change_cnt);
        }

        int delete_cnt = s.length() - 20;
        
        total_change_cnt -= min(delete_cnt, one_change_cnt) / 1;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2;
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3;
            
        return delete_cnt + max(missing_type_cnt, total_change_cnt);
    }


