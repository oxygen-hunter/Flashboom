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


    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        const auto n = nums.size();
        vector<int> accu = {0};
        for (const auto& num : nums) {
            accu.emplace_back(accu.back() + num);
        }
       
        vector<int> left_pos(n);
        for (int i = k, total = accu[k] - accu[0]; i < n; ++i) {
            if (accu[i + 1] - accu[i + 1 - k] > total) {
                left_pos[i] = i + 1 - k;
                total = accu[i + 1] - accu[i + 1 - k];
            } else { 
                left_pos[i] = left_pos[i - 1];
            }
        }
        
        vector<int> right_pos(n, n - k);
        for (int i = n - k - 1, total = accu[n] - accu[n - k]; i >= 0; --i) {
            if (accu[i + k] - accu[i] > total) {
                right_pos[i] = i;
                total = accu[i + k] - accu[i];
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }
        
        vector<int> result(3);
        for (int i = k, max_sum = 0; i <= n - 2 * k; ++i) {
            auto left = left_pos[i - 1], right = right_pos[i + k];
            auto total = (accu[i + k] - accu[i]) +
                         (accu[left + k] - accu[left]) +
                         (accu[right + k] - accu[right]);
            if (total > max_sum) {
                max_sum = total;
                result = {left, i, right};
            }
        }
        return result;
    }


