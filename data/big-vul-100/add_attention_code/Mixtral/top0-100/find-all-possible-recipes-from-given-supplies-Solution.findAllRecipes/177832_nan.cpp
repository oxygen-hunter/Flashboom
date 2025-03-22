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

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, int> indegree;
        unordered_map<string, vector<string>> adj;
        for (int i = 0; i < size(recipes); ++i) {
            indegree[recipes[i]] = size(ingredients[i]);
            for (const auto& ing : ingredients[i]) {
                adj[ing].emplace_back(recipes[i]);
            }
        }
        vector<string> result;
        unordered_set<string> recipes_set(cbegin(recipes), cend(recipes));
        vector<string> q = supplies;
        while (!empty(q)) { 
            vector<string> new_q;
            for (const auto& u : q) {
                if (recipes_set.count(u)) {
                    result.emplace_back(u);
                }
                for (const auto& v : adj[u]) {
                    if (!--indegree[v]) {
                        new_q.emplace_back(v);
                    }
                }
            }
            q = move(new_q);
        }
        return result ;
    }

