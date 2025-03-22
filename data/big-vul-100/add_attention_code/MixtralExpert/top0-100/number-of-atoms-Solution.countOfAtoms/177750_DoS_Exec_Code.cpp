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


    string countOfAtoms(string formula) {
        stack<map<string, int>> stk;
        stk.emplace();
        int submatches[] = { 1, 2, 3, 4, 5 };
        const auto e = regex("([A-Z][a-z]*)(\\d*)|(\\()|(\\))(\\d*)");
        for (regex_token_iterator<string::iterator> it(formula.begin(), formula.end(), e, submatches), end;
             it != end;) {
            const auto& name = (it++)->str();
            const auto& m1 = (it++)->str();
            const auto& left_open = (it++)->str();
            const auto& right_open = (it++)->str();
            const auto& m2 = (it++)->str();
            if (!name.empty()) {
                stk.top()[name] += stoi(!m1.empty() ? m1 : "1");
            }
            if (!left_open.empty()) {
                stk.emplace();
            }
            if (!right_open.empty()) {
                const auto top = move(stk.top()); stk.pop();
                for (const auto& kvp: top) {
                    stk.top()[kvp.first] += kvp.second * stoi(!m2.empty() ? m2 : "1");
                }
            }
        }
        string result;
        for (const auto& kvp : stk.top()) {
            result += kvp.first;
            if (kvp.second > 1) {
                result += to_string(kvp.second);
            }
        }
        return result;
    }


