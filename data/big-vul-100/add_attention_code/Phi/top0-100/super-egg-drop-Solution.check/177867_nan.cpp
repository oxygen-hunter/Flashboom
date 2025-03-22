gs_main_finit(gs_main_instance * minst, int exit_status, int code)
{
    i_ctx_t *i_ctx_p = minst->i_ctx_p;
    gs_dual_memory_t dmem = {0};
    int exit_code;
    ref error_object;
    char *tempnames;

    /* NB: need to free gs_name_table
     */

    /*
     * Previous versions of this code closed the devices in the
     * device list here.  Since these devices are now prototypes,
     * they cannot be opened, so they do not need to be closed;
     * alloc_restore_all will close dynamically allocated devices.
     */
    tempnames = gs_main_tempnames(minst);

    /* by the time we get here, we *must* avoid any random redefinitions of
     * operators etc, so we push systemdict onto the top of the dict stack.
     * We do this in C to avoid running into any other re-defininitions in the
     * Postscript world.
     */
    gs_finit_push_systemdict(i_ctx_p);

    /* We have to disable BGPrint before we call interp_reclaim() to prevent the
     * parent rendering thread initialising for the next page, whilst we are
     * removing objects it may want to access - for example, the I/O device table.
     * We also have to mess with the BeginPage/EndPage procs so that we don't
     * trigger a spurious extra page to be emitted.
     */
    if (minst->init_done >= 2) {
        gs_main_run_string(minst,
            "/BGPrint /GetDeviceParam .special_op \
            {{ <</BeginPage {pop} /EndPage {pop pop //false } \
              /BGPrint false /NumRenderingThreads 0>> setpagedevice} if} if \
              serverdict /.jobsavelevel get 0 eq {/quit} {/stop} ifelse \
              .systemvar exec",
            0 , &exit_code, &error_object);
    }

    /*
     * Close the "main" device, because it may need to write out
     * data before destruction. pdfwrite needs so.
     */
    if (minst->init_done >= 2) {
        int code = 0;

        if (idmemory->reclaim != 0) {
            code = interp_reclaim(&minst->i_ctx_p, avm_global);

            if (code < 0) {
                ref error_name;
                if (tempnames)
                    free(tempnames);

                if (gs_errorname(i_ctx_p, code, &error_name) >= 0) {
                    char err_str[32] = {0};
                    name_string_ref(imemory, &error_name, &error_name);
                    memcpy(err_str, error_name.value.const_bytes, r_size(&error_name));
                    emprintf2(imemory, "ERROR: %s (%d) reclaiming the memory while the interpreter finalization.\n", err_str, code);
                }
                else {
                    emprintf1(imemory, "UNKNOWN ERROR %d reclaiming the memory while the interpreter finalization.\n", code);
                }
#ifdef MEMENTO_SQUEEZE_BUILD
                if (code != gs_error_VMerror ) return gs_error_Fatal;
#else
                return gs_error_Fatal;
#endif
            }
             i_ctx_p = minst->i_ctx_p; /* interp_reclaim could change it. */
         }
 
         if (i_ctx_p->pgs != NULL && i_ctx_p->pgs->device != NULL) {
             gx_device *pdev = i_ctx_p->pgs->device;
             const char * dname = pdev->dname;
            if (code < 0) {
                ref error_name;
                if (gs_errorname(i_ctx_p, code, &error_name) >= 0) {
                    char err_str[32] = {0};
                    name_string_ref(imemory, &error_name, &error_name);
                    memcpy(err_str, error_name.value.const_bytes, r_size(&error_name));
                    emprintf3(imemory, "ERROR: %s (%d) on closing %s device.\n", err_str, code, dname);
                }
                else {
                    emprintf2(imemory, "UNKNOWN ERROR %d closing %s device.\n", code, dname);
               }
            }
            rc_decrement(pdev, "gs_main_finit");                /* device might be freed */
            if (exit_status == 0 || exit_status == gs_error_Quit)
                exit_status = code;
        }

      /* Flush stdout and stderr */
      gs_main_run_string(minst,
        "(%stdout) (w) file closefile (%stderr) (w) file closefile \
        serverdict /.jobsavelevel get 0 eq {/quit} {/stop} ifelse .systemexec \
          systemdict /savedinitialgstate .forceundef",
        0 , &exit_code, &error_object);
    }
    gp_readline_finit(minst->readline_data);
    i_ctx_p = minst->i_ctx_p;		/* get current interp context */
    if (gs_debug_c(':')) {
        print_resource_usage(minst, &gs_imemory, "Final");
        dmprintf1(minst->heap, "%% Exiting instance 0x%p\n", minst);
    }
    /* Do the equivalent of a restore "past the bottom". */
    /* This will release all memory, close all open files, etc. */
    if (minst->init_done >= 1) {
        gs_memory_t *mem_raw = i_ctx_p->memory.current->non_gc_memory;
        i_plugin_holder *h = i_ctx_p->plugin_list;

        dmem = *idmemory;
        code = alloc_restore_all(i_ctx_p);
        if (code < 0)
            emprintf1(mem_raw,
                      "ERROR %d while the final restore. See gs/psi/ierrors.h for code explanation.\n",
                      code);
        i_iodev_finit(&dmem);
        i_plugin_finit(mem_raw, h);
    }

    /* clean up redirected stdout */
    if (minst->heap->gs_lib_ctx->fstdout2
        && (minst->heap->gs_lib_ctx->fstdout2 != minst->heap->gs_lib_ctx->fstdout)
        && (minst->heap->gs_lib_ctx->fstdout2 != minst->heap->gs_lib_ctx->fstderr)) {
        fclose(minst->heap->gs_lib_ctx->fstdout2);
        minst->heap->gs_lib_ctx->fstdout2 = (FILE *)NULL;
    }

    minst->heap->gs_lib_ctx->stdout_is_redirected = 0;
    minst->heap->gs_lib_ctx->stdout_to_stderr = 0;
    /* remove any temporary files, after ghostscript has closed files */
    if (tempnames) {
        char *p = tempnames;
        while (*p) {
            unlink(p);
            p += strlen(p) + 1;
        }
        free(tempnames);
    }
    gs_lib_finit(exit_status, code, minst->heap);

    gs_free_object(minst->heap, minst->lib_path.container.value.refs, "lib_path array");
    ialloc_finit(&dmem);
    return exit_status;
}

    bool check(int n, int K, int N) {
        // let f(n, K) be the max number of floors could be solved by n moves and K eggs,
        // we want to do binary search to find min of n, s.t. f(n, K) >= N,
        // if we use one move to drop egg with X floors
        // 1. if it breaks, we can search new X in the range [X+1, X+f(n-1, K-1)]
        // 2. if it doesn't break, we can search new X in the range [X-f(n-1, K), X-1]
        // => f(n, K) = (X+f(n-1, K-1))-(X-f(n-1, K))+1 = f(n-1, K-1)+f(n-1, K)+1
        // => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
        //    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
        // let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
        // => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
	    // => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
        //    which also implies if we have one more egg with n moves and x-1 egges, we can have more C(n, x) floors solvable
        // => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
        // => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
        //    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each sucess and failure sequence of every C(n, k) combinations for k in [1, K]
        int total = 0, c = 1;
        for (int k = 1; k <= K; ++k) {
            c *= n - k + 1;
            c /= k;
            total += c;
            if (total >= N) {
                return true;
            }
        }
        return false;
    }

