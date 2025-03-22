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

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        const auto& binary_search = [](int left, int right, const auto& check) {
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        const auto& findKthInSortedArrays = [&](const auto& arrays, int k) {
            const auto& check = [&](int num) {
                int res = 0;
                for (const auto& arr : arrays) {
                    if (!empty(*arr)) {  // count the number of values which are less or equal to num
                        res += distance(cbegin(*arr), upper_bound(cbegin(*arr), cend(*arr), num));
                    }
                }
                return res >= k;
            };

            int left = numeric_limits<int>::max();
            int right = numeric_limits<int>::min();
            for (const auto arr : arrays) {
                if (!empty(*arr)) {
                    left = min(left, arr->front());
                    right = max(right, arr->back());
                }
            }
            return binary_search(left, right, check);
        };

        vector<vector<int> *> arrays{&nums1, &nums2};
        int total = accumulate(cbegin(arrays), cend(arrays), 0, [](const auto& x, const auto& y) {
            return x + size(*y);
        });
        if (total % 2 == 1) {
            return findKthInSortedArrays(arrays, total / 2 + 1);
        } else {
            return (findKthInSortedArrays(arrays, total / 2) +
                    findKthInSortedArrays(arrays, total / 2 + 1)) / 2.0;
        }
    }

