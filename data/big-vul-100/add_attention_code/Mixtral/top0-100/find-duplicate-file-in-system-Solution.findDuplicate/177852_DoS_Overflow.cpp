parse_object(JsonLexContext *lex, JsonSemAction *sem)
{
	/*
	 * an object is a possibly empty sequence of object fields, separated by
	 * commas and surrounded by curly braces.
	 */
	json_struct_action ostart = sem->object_start;
    json_struct_action oend = sem->object_end;
    JsonTokenType tok;
 
    if (ostart != NULL)
        (*ostart) (sem->semstate);
 
	 * itself. Note that we increment this after we call the semantic routine
	 * for the object start and restore it before we call the routine for the
	 * object end.
	 */
	lex->lex_level++;

	/* we know this will succeeed, just clearing the token */
	lex_expect(JSON_PARSE_OBJECT_START, lex, JSON_TOKEN_OBJECT_START);

	tok = lex_peek(lex);
	switch (tok)
	{
		case JSON_TOKEN_STRING:
			parse_object_field(lex, sem);
			while (lex_accept(lex, JSON_TOKEN_COMMA, NULL))
				parse_object_field(lex, sem);
			break;
		case JSON_TOKEN_OBJECT_END:
			break;
		default:
			/* case of an invalid initial token inside the object */
			report_parse_error(JSON_PARSE_OBJECT_START, lex);
	}

	lex_expect(JSON_PARSE_OBJECT_NEXT, lex, JSON_TOKEN_OBJECT_END);

	lex->lex_level--;

	if (oend != NULL)
		(*oend) (sem->semstate);
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

