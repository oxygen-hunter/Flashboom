mcid_char_imp(fz_context *ctx, pdf_filter_processor *p, tag_record *tr, int uni, int remove)
{
	if (tr->mcid_obj == NULL)
		/* No object, or already deleted */
		return;

	if (remove)
	{
		/* Remove the expanded abbreviation, if there is one. */
		pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(E));
                /* Remove the structure title, if there is one. */
                pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(T));
        }
        /* Edit the Alt string */
        walk_string(ctx, uni, remove, &tr->alt);
        /* Edit the ActualText string */
        walk_string(ctx, uni, remove, &tr->actualtext);
        /* If we're removing a character, and either of the strings
         * haven't matched up to what we were expecting, then just
         * delete the whole string. */
	else if (tr->alt.pos >= 0 || tr->actualtext.pos >= 0)
	{
		/* The strings are making sense so far */
		remove = 0;
                /* The strings are making sense so far */
                remove = 0;
        }
        if (remove)
        {
                /* Anything else we have to err on the side of caution and
		if (tr->alt.pos == -1)
			pdf_dict_del(ctx, tr->mcid_obj, PDF_NAME(Alt));
		pdf_drop_obj(ctx, tr->mcid_obj);
		tr->mcid_obj = NULL;
		fz_free(ctx, tr->alt.utf8);
		tr->alt.utf8 = NULL;
		fz_free(ctx, tr->actualtext.utf8);
		tr->actualtext.utf8 = NULL;
	}
}

    int triangularSum(vector<int>& nums) {
        const auto& exp_mod = [](const auto& p, const auto& mod) {
            vector<int> result = {p};
            while (result.back() * p % 10 != result[0]) {
                 result.emplace_back(result.back() * p %10);
            }
            rotate(rbegin(result), rbegin(result) + 1, rend(result));
            return result;
        };
        const auto& inv_mod = [](const auto& x, const auto& mod) {
            int y = x;
            while (y * x % 10 != 1) {
                y = y * x % 10;
            }
            return y;
        };
        const auto& factor_p = [](auto x, const auto& p, auto cnt, auto diff) {
            if (x == 0) {
                return make_pair(x, cnt);
            }
            while (x % p == 0) {
                x /= p;
                cnt += diff;
            }
            return make_pair(x, cnt);
        };
    
        const unordered_map<int, vector<int>> EXP = {{2, exp_mod(2, 10)}, {5, exp_mod(5, 10)}};  // {2:[6, 2, 4, 8], 5:[5]}
        const unordered_map<int, int> INV = {{1, inv_mod(1, 10)}, {3, inv_mod(3, 10)}, {7, inv_mod(7, 10)}, {9, inv_mod(9, 10)}};  // {1:1, 3:7, 7:3, 9:9}
        int result = 0;
        int nCr = 1;
        unordered_map<int, int> cnt = {{2, 0}, {5, 0}};
        for (int i = 0; i < size(nums); ++i) {
            if (!cnt[2] && !cnt[5]) {
                result = (result + nCr * nums[i]) % 10;
            } else if (cnt[2] && !cnt[5]) {
                result = (result + nCr * EXP.at(2)[cnt[2] % size(EXP.at(2))] * nums[i]) % 10;
            } else if (!cnt[2] && cnt[5]) {
                result = (result + nCr*EXP.at(5)[cnt[5] % size(EXP.at(5))] * nums[i]) % 10;
            }
            int mul = (size(nums) - 1) - i;
            tie(mul, cnt[2]) = factor_p(mul, 2, cnt[2], 1);
            tie(mul, cnt[5]) = factor_p(mul, 5, cnt[5], 1);
            int div = i + 1;
            tie(div, cnt[2]) = factor_p(div, 2, cnt[2], -1);
            tie(div, cnt[5]) = factor_p(div, 5, cnt[5], -1);
            nCr = nCr * mul % 10;
            nCr = nCr * INV.at(div % 10) % 10;
        }
        return result;
    }

