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


    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        using P = pair<int, int>;
        unordered_map<int, vector<P>> adj;
        for (const auto& flight : flights) {
            int u, v, w;
            tie(u, v, w) = make_tuple(flight[0], flight[1], flight[2]);
            adj[u].emplace_back(v, w);
        }
        
        unordered_map<int, unordered_map<int, int>> best;
        best[src][K + 1] = 0;
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0, src, K + 1);
        while (!min_heap.empty()) {
            int result, u, k;
            tie(result, u, k) = min_heap.top(); min_heap.pop();
            if (k < 0 ||
                (best.count(u) && best[u].count(k) &&  best[u][k] < result)) {
                continue;
            }
            if (u == dst) {
                return result;
            }
            for (const auto& kvp : adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                if (!best.count(v) ||
                    !best[v].count(k - 1) ||
                    result + w < best[v][k - 1]) {
                    best[v][k - 1] = result + w;
                    min_heap.emplace(result + w, v, k - 1);
                }
            }
        }
        return -1;
    }


