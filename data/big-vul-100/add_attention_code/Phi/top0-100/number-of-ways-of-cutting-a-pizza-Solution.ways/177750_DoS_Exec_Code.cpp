begin_softmask(fz_context *ctx, pdf_run_processor *pr, softmask_save *save)
{
	pdf_gstate *gstate = pr->gstate + pr->gtop;
	pdf_xobject *softmask = gstate->softmask;
	fz_rect mask_bbox;
	fz_matrix tos_save[2], save_ctm;
	fz_matrix mask_matrix;
	fz_colorspace *mask_colorspace;

	save->softmask = softmask;
	if (softmask == NULL)
		return gstate;
	save->page_resources = gstate->softmask_resources;
	save->ctm = gstate->softmask_ctm;
	save_ctm = gstate->ctm;

	pdf_xobject_bbox(ctx, softmask, &mask_bbox);
	pdf_xobject_matrix(ctx, softmask, &mask_matrix);

	pdf_tos_save(ctx, &pr->tos, tos_save);

	if (gstate->luminosity)
		mask_bbox = fz_infinite_rect;
	else
	{
		fz_transform_rect(&mask_bbox, &mask_matrix);
		fz_transform_rect(&mask_bbox, &gstate->softmask_ctm);
	}
	gstate->softmask = NULL;
	gstate->softmask_resources = NULL;
	gstate->ctm = gstate->softmask_ctm;

        mask_colorspace = pdf_xobject_colorspace(ctx, softmask);
 
        if (gstate->luminosity && !mask_colorspace)
               mask_colorspace = fz_device_gray(ctx);
 
        fz_try(ctx)
        {
		fz_begin_mask(ctx, pr->dev, &mask_bbox, gstate->luminosity, mask_colorspace, gstate->softmask_bc, &gstate->fill.color_params);
		pdf_run_xobject(ctx, pr, softmask, save->page_resources, &fz_identity, 1);
	}
	fz_always(ctx)
		fz_drop_colorspace(ctx, mask_colorspace);
	fz_catch(ctx)
	{
		fz_rethrow_if(ctx, FZ_ERROR_TRYLATER);
		/* FIXME: Ignore error - nasty, but if we throw from
		 * here the clip stack would be messed up. */
		/* TODO: pass cookie here to increase the cookie error count */
	}

	fz_end_mask(ctx, pr->dev);

	pdf_tos_restore(ctx, &pr->tos, tos_save);

	gstate = pr->gstate + pr->gtop;
	gstate->ctm = save_ctm;

	return gstate;
}

    int ways(vector<string>& pizza, int k) {
        static int MOD = 1e9 + 7;
        vector<vector<int>> prefix(pizza.size(), vector<int>(pizza[0].size()));
        for (int j = pizza[0].size() - 1; j >= 0; --j) {
            for (int accu = 0, i = pizza.size() - 1; i >= 0; --i) {
                accu += pizza[i][j] == 'A';
                prefix[i][j] = ((j + 1 != pizza[0].size()) ? prefix[i][j + 1] : 0) + accu;
            }
        }
        vector<vector<vector<uint64_t>>> dp(pizza.size(),
                                            vector<vector<uint64_t>>(pizza[0].size(),
                                            vector<uint64_t>(k)));
        for (int i = pizza.size() - 1; i >= 0; --i) {
            for (int j = pizza[0].size() - 1; j >= 0; --j) {
                dp[i][j][0] = 1;
                for (int m = 1; m < k; ++m) {
                    for (int n = i + 1; n < pizza.size() && prefix[n][j]; ++n) {
                        if (prefix[i][j] == prefix[n][j]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[n][j][m - 1]) % MOD;
                    }
                    for (int n = j + 1; n < pizza[0].size() && prefix[i][n]; ++n) {
                        if (prefix[i][j] == prefix[i][n]) {
                            continue;
                        }
                        dp[i][j][m] = (dp[i][j][m] + dp[i][n][m - 1]) % MOD;
                    }
                }
            }
        }
        return dp[0][0][k - 1];
    }

