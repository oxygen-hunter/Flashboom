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

    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {
        static const int INF = numeric_limits<int>::max();
        const auto& check = [&](int mask, const auto& dist) {
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) == 0) {
                    continue;
                }
                for (int j = i + 1; j < n; ++j) {
                    if ((mask & (1 << j)) == 0) {
                        continue;
                    }
                    if (dist[i][j] > maxDistance) {
                        return false;
                    }
                }
            }
            return true;
        };

        const auto& floydWarshall = [&](int mask, auto dist) {
            for (int k = 0; k < n; ++k) {
                if ((mask & (1 << k)) == 0) {
                    continue;
                }
                for (int i = 0; i < n; ++i) {
                    if ((mask & (1 << i)) == 0) {  // optional, to speed up performance
                        continue;
                    }
                    for (int j = i + 1; j < n; ++j) {
                        if ((mask & (1 << j)) == 0) {  // optional, to speed up performance
                            continue;
                        }
                        if (dist[i][k] != INF && dist[k][j] != INF) {
                            dist[j][i] = dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
            return check(mask, dist);
        };

        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int u = 0; u < n; ++u) {
            dist[u][u] = 0;
        }
        for (const auto& r : roads) {
            dist[r[0]][r[1]] = min(dist[r[0]][r[1]], r[2]);
            dist[r[1]][r[0]] = min(dist[r[1]][r[0]], r[2]);
        }
        int result = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            result += floydWarshall(mask, dist);
        }
        return result;
    }

