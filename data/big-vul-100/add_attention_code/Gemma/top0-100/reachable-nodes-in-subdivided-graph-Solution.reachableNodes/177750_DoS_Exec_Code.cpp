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


    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        using P = pair<int, int>;
        vector<vector<P>> adj(N);
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }
        unordered_map<int, int> best;
        best[0] = 0;
        unordered_map<int, unordered_map<int, int>> count;
        int result = 0;
        priority_queue<P, vector<P>, greater<P>> min_heap;
        min_heap.emplace(0, 0);
        while (!min_heap.empty()) {
            int curr_total, u;
            tie(curr_total, u) = min_heap.top(); min_heap.pop();
            if (best.count(u) && best[u] < curr_total) {
                continue;
            }
            ++result;
            for (const auto& kvp: adj[u]) {
                int v, w;
                tie(v, w) = kvp;
                count[u][v] = min(w, M - curr_total);
                int next_total = curr_total + w + 1;
                if (next_total <= M && 
                    (!best.count(v) || next_total < best[v])) {
                    best[v] = next_total;
                    min_heap.emplace(next_total, v);
                }
            }
        }
        for (const auto& edge: edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            result += min(w, count[u][v] + count[v][u]);
        }
        return result;
    }


