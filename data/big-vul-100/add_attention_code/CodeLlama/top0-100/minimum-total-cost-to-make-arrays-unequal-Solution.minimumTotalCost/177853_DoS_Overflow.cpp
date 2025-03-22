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


    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnt;
        int64_t result = 0;
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] != nums2[i]) {
                continue;
            }
            ++cnt[nums1[i]];
            result += i;
        }
        if (empty(cnt)) {
            return 0;
        }
        const int majority = max_element(cbegin(cnt), cend(cnt),
                                         [](const auto& a, const auto& b) {
                                                return a.second < b.second;
                                         })->first;
        int remain = cnt[majority] - (accumulate(cbegin(cnt), cend(cnt), 0,
                                                 [](const auto& total, const auto& x) {
                                                     return total + x.second;
                                                 }) - cnt[majority]);
        if (remain <= 0) {
            return result;
        }
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] == nums2[i] || nums1[i] == majority || nums2[i] == majority) {
                continue;
            }
            result += i;
            if (--remain == 0) {
                return result;
            }
        }
        return -1;
    }


