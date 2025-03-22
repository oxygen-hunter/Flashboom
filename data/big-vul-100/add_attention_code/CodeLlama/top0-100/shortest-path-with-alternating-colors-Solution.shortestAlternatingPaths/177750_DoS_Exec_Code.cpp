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


    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        vector<vector<unordered_set<int>>> neighbors(n, vector<unordered_set<int>>(2));
        for (const auto& edge : red_edges) {
            neighbors[edge[0]][0].emplace(edge[1]);
        }
        for (const auto& edge : blue_edges) {
            neighbors[edge[0]][1].emplace(edge[1]);
        }
        const auto& INF = max(2 * n - 3, 0) + 1;
        vector<vector<int>> dist(n, vector<int>(2, INF));
        dist[0] = {0, 0};
        queue<pair<int, int>> q({{0, 0}, {0, 1}});
        while (!q.empty()) {
            int i, c;
            tie(i, c) = q.front(); q.pop();
            for (const auto& j : neighbors[i][c]) {
                if (dist[j][c] != INF) {
                    continue;
                }
                dist[j][c] = dist[i][1 ^ c] + 1;
                q.emplace(j, 1 ^ c);
            }
        }
        vector<int> result;
        for (const auto& d : dist) {
            const auto& x = *min_element(d.cbegin(), d.cend());
            result.emplace_back((x != INF) ? x : -1);
        }
        return result;
    }


