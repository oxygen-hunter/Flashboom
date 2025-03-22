setPath(JsonbIterator **it, Datum *path_elems,
		bool *path_nulls, int path_len,
		JsonbParseState **st, int level, Jsonb *newval, bool create)
{
	JsonbValue	v;
    JsonbValue *res = NULL;
    int         r;
 
    if (path_nulls[level])
        elog(ERROR, "path element at the position %d is NULL", level + 1);
	switch (r)
	{
		case WJB_BEGIN_ARRAY:
			(void) pushJsonbValue(st, r, NULL);
			setPathArray(it, path_elems, path_nulls, path_len, st, level,
						 newval, v.val.array.nElems, create);
			r = JsonbIteratorNext(it, &v, false);
			Assert(r == WJB_END_ARRAY);
			res = pushJsonbValue(st, r, NULL);

			break;
		case WJB_BEGIN_OBJECT:
			(void) pushJsonbValue(st, r, NULL);
			setPathObject(it, path_elems, path_nulls, path_len, st, level,
						  newval, v.val.object.nPairs, create);
			r = JsonbIteratorNext(it, &v, true);
			Assert(r == WJB_END_OBJECT);
			res = pushJsonbValue(st, r, NULL);

			break;
		case WJB_ELEM:
		case WJB_VALUE:
			res = pushJsonbValue(st, r, &v);
			break;
		default:
			elog(ERROR, "impossible state");
	}

	return res;
}

    bool areSentencesSimilar(string sentence1, string sentence2) {
        if (size(sentence1) > size(sentence2)) {
            swap(sentence1, sentence2);
        }
        int count = 0;
        for (int step = 0; step < 2; ++step) {
            for (int i = 0; i <= size(sentence1); ++i) {
                char c1 = i != size(sentence1) ? sentence1[step == 0 ? i : size(sentence1) - 1 - i] : ' ';
                char c2 = i != size(sentence2) ? sentence2[step == 0 ? i : size(sentence2) - 1 - i] : ' ';
                if (c1 != c2) {
                    break;
                }
                if (c1 == ' ') {
                    ++count;
                }
            }
        }
        return count >= count_if(cbegin(sentence1), cend(sentence1),
                                 [](char x) { return x == ' '; }) + 1;
    }

