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

