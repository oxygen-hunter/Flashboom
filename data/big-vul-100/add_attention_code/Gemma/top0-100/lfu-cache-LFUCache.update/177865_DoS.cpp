PatternMatch(char *pat, int patdashes, char *string, int stringdashes)
{
    char        c,
                t;

    if (stringdashes < patdashes)
	return 0;
    for (;;) {
	switch (c = *pat++) {
	case '*':
	    if (!(c = *pat++))
		return 1;
	    if (c == XK_minus) {
		patdashes--;
		for (;;) {
		    while ((t = *string++) != XK_minus)
			if (!t)
			    return 0;
		    stringdashes--;
		    if (PatternMatch(pat, patdashes, string, stringdashes))
			return 1;
		    if (stringdashes == patdashes)
			return 0;
		}
	    } else {
		for (;;) {
		    while ((t = *string++) != c) {
			if (!t)
			    return 0;
			if (t == XK_minus) {
			    if (stringdashes-- < patdashes)
				return 0;
			}
		    }
		    if (PatternMatch(pat, patdashes, string, stringdashes))
			return 1;
 		}
 	    }
 	case '?':
	    if (*string++ == XK_minus)
 		stringdashes--;
 	    break;
 	case '\0':
 	    return (*string == '\0');
		patdashes--;
		stringdashes--;
		break;
	    }
	    return 0;
	default:
	    if (c == *string++)
		break;
	    return 0;
	}
    }


    void update(int key, int value) {
        int freq = 0;
        if (key_to_nodeit_.count(key)) {
            auto old_node = *key_to_nodeit_[key];        
            freq = std::get<FREQ>(old_node);
            freq_to_nodes_[freq].erase(key_to_nodeit_[key]);
            if (freq_to_nodes_[freq].empty()) {
                freq_to_nodes_.erase(freq);
                if (min_freq_ == freq) {
                    ++min_freq_;
                }
            }
            --size_;
        }
        min_freq_ = min(min_freq_, ++freq);
        freq_to_nodes_[freq].emplace_back(key, value, freq);
        key_to_nodeit_[key] = prev(freq_to_nodes_[freq].end());
        ++size_;
    }


