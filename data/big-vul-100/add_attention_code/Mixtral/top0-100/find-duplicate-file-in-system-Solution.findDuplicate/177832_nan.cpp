walk_string(fz_context *ctx, int uni, int remove, editable_str *str)
 {
        int rune;
 
       if (str->utf8 == NULL)
                return;
 
        do
	{
		char *s = &str->utf8[str->pos];
		size_t len;
		int n = fz_chartorune(&rune, s);
		if (rune == uni)
		{
			/* Match. Skip over that one. */
			str->pos += n;
		}
		else if (uni == 32) {
			/* We don't care if we're given whitespace
			 * and it doesn't match the string. Don't
			 * skip forward. Nothing to remove. */
			break;
		}
		else if (rune == 32) {
			/* The string has a whitespace, and we
			 * don't match it; that's forgivable as
			 * PDF often misses out spaces. Remove this
			 * if we are removing stuff. */
		}
		else
		{
			/* Mismatch. No point in tracking through any more. */
			str->pos = -1;
			break;
		}
		if (remove)
		{
			len = strlen(s+n);
			memmove(s, s+n, len+1);
			str->edited = 1;
		}
	}
	while (rune != uni);
}

    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> files;
        for (const auto& path : paths) {
    	    stringstream ss(path);
    	    string root;
    	    string s;
    	    getline(ss, root, ' ');
    	    while (getline(ss, s, ' ')) {
    		    auto fileName = root + '/' + s.substr(0, s.find('('));
    		    auto fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
    		    files[fileContent].emplace_back(fileName);
    	    }
        }
    
        vector<vector<string>> result;
        for (const auto& file : files) {
    	    if (file.second.size() > 1) {
    		    result.emplace_back(file.second);
    	    }
        }
        return result;
    }

