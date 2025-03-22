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

    int countQuadruples(string firstString, string secondString) {
        vector<int> lookup1(26, -1);
        for (int i = size(firstString) - 1; i >= 0; --i) {
            lookup1[firstString[i] - 'a'] = i;
        }
        vector<int> lookup2(26, -1);
        for (int i = 0; i < size(secondString); ++i) {
            lookup2[secondString[i] - 'a'] = i;
        }
        int result = 0, diff = numeric_limits<int>::max();
        for (int i = 0; i < 26; ++i) {
            if (lookup1[i] == -1 || lookup2[i] == -1) {
                continue;
            }
            if (lookup1[i] - lookup2[i] < diff) {
                diff = lookup1[i] - lookup2[i];
                result = 0;
            }                
            result += int(lookup1[i] - lookup2[i] == diff);                
        }
        return result;
    }

