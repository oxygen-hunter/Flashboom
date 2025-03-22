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


