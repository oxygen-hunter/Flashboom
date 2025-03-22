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

    bool sumGame(string num) {
        // (1) if both halfs have '?',
        //     alice will optimally choose 9 or 0 from one half to maximize or minimize the diff of both half sums,
        //     and bob will optimally choose the same number from the other half to minimize or maximize the diff of both half sums.
        //     in the end, it turns that only one half has '?' and the diff of both half sums is still the same as original
        // (2) if smaller half has no '?', then alice wins
        // (3) if smaller half has '?'
        //     (3.1) if cnt of '?' is odd, alice can choose the last number to make the diff of both half sums != 0, then alice wins
        //     (3.2) if cnt of '?' is even
        //           (3.2.1) if larger-smaller = cnt/2 * 9, bob can always make a pair of sum 9 no matter what alice chooses, then bob wins
        //           (3.2.2) if larger-smaller > cnt/2 * 9, alice can always choose 0 no matter what bob chooses, then alice wins
        //           (3.2.3) if larger-smaller < cnt/2 * 9, alice can always choose 9 no matter what bob chooses, then alice wins
        int cnt = 0, total = 0;
        for (int i = 0; i < size(num); ++i) {
            if (num[i] == '?') {
                cnt += (i < size(num) / 2) ? -1 : 1;
            } else {
                total += (i < size(num) / 2) ? num[i] - '0' : -(num[i] - '0');
            }
        }
        return cnt % 2 ? true : total != cnt / 2 * 9;
    }

