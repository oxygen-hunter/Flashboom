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

    vector<vector<int>> highestRankedKItems(vector<vector<int>>& grid, vector<int>& pricing, vector<int>& start, int k) {
        static const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        vector<pair<int, int>> q = {{start[0], start[1]}};
        vector<vector<int>> lookup(size(grid), vector<int>(size(grid[0]), -1));
        int d = lookup[start[0]][start[1]] = 0;
        auto compare = [&](const auto& x, const auto& y) {
            return make_tuple(lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1]) <
                   make_tuple(lookup[y[0]][y[1]], grid[y[0]][y[1]], y[0], y[1]);
        };
        vector<vector<int>> result;
        while (!empty(q)) {
            if (size(result) >= k) {
                if (size(result) > k) {
                    nth_element(begin(result), begin(result) + k, end(result), compare);
                    result.resize(k);
                }
                break;
            }
            vector<pair<int, int>> new_q;
            for (const auto& [r, c] : q) {
                if (pricing[0] <= grid[r][c] && grid[r][c] <= pricing[1]) {
                    result.push_back({r, c});
                }
                for (const auto& [dr, dc] : directions) {
                    const int nr = r + dr, nc = c + dc;
                    if (!((0 <= nr && nr < size(grid)) && (0 <= nc && nc < size(grid[0])) &&
                           grid[nr][nc] && lookup[nr][nc] == -1)) {
                        continue;
                    }
                    lookup[nr][nc] = d + 1;
                    new_q.emplace_back(nr, nc);
                }
            }
            q = move(new_q);
            ++d;
        }
        sort(begin(result), end(result), compare);
        return result;
    }

