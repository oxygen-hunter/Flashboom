do_ed_script (char const *inname, char const *outname,
	      bool *outname_needs_removal, FILE *ofp)
{
    static char const editor_program[] = EDITOR_PROGRAM;

    file_offset beginning_of_this_line;
    size_t chars_read;
    FILE *tmpfp = 0;
    char const *tmpname;
    int tmpfd;
    pid_t pid;

    if (! dry_run && ! skip_rest_of_patch)
      {
	/* Write ed script to a temporary file.  This causes ed to abort on
	   invalid commands such as when line numbers or ranges exceed the
	   number of available lines.  When ed reads from a pipe, it rejects
	   invalid commands and treats the next line as a new command, which
	   can lead to arbitrary command execution.  */

	tmpfd = make_tempfile (&tmpname, 'e', NULL, O_RDWR | O_BINARY, 0);
	if (tmpfd == -1)
	  pfatal ("Can't create temporary file %s", quotearg (tmpname));
	tmpfp = fdopen (tmpfd, "w+b");
	if (! tmpfp)
	  pfatal ("Can't open stream for file %s", quotearg (tmpname));
      }

    for (;;) {
	char ed_command_letter;
	beginning_of_this_line = file_tell (pfp);
	chars_read = get_line ();
	if (! chars_read) {
	    next_intuit_at(beginning_of_this_line,p_input_line);
	    break;
	}
	ed_command_letter = get_ed_command_letter (buf);
	if (ed_command_letter) {
	    if (tmpfp)
		if (! fwrite (buf, sizeof *buf, chars_read, tmpfp))
		    write_fatal ();
	    if (ed_command_letter != 'd' && ed_command_letter != 's') {
	        p_pass_comments_through = true;
		while ((chars_read = get_line ()) != 0) {
		    if (tmpfp)
			if (! fwrite (buf, sizeof *buf, chars_read, tmpfp))
			    write_fatal ();
		    if (chars_read == 2  &&  strEQ (buf, ".\n"))
			break;
		}
		p_pass_comments_through = false;
	    }
	}
	else {
	    next_intuit_at(beginning_of_this_line,p_input_line);
	    break;
	}
    }
    if (!tmpfp)
      return;
    if (fwrite ("w\nq\n", sizeof (char), (size_t) 4, tmpfp) == 0
	|| fflush (tmpfp) != 0)
      write_fatal ();

    if (lseek (tmpfd, 0, SEEK_SET) == -1)
      pfatal ("Can't rewind to the beginning of file %s", quotearg (tmpname));

    if (! dry_run && ! skip_rest_of_patch) {
	int exclusive = *outname_needs_removal ? 0 : O_EXCL;
	*outname_needs_removal = true;
	if (inerrno != ENOENT)
	  {
 	    *outname_needs_removal = true;
 	    copy_file (inname, outname, 0, exclusive, instat.st_mode, true);
 	  }
	sprintf (buf, "%s %s%s", editor_program,
		 verbosity == VERBOSE ? "" : "- ",
		 outname);
 	fflush (stdout);
 
 	pid = fork();
	fflush (stdout);

 	else if (pid == 0)
 	  {
 	    dup2 (tmpfd, 0);
	    execl ("/bin/sh", "sh", "-c", buf, (char *) 0);
 	    _exit (2);
 	  }
 	else
	  }
	else
	  {
	    int wstatus;
	    if (waitpid (pid, &wstatus, 0) == -1
	        || ! WIFEXITED (wstatus)
		|| WEXITSTATUS (wstatus) != 0)
	      fatal ("%s FAILED", editor_program);
	  }
    }

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        const auto& topological_sort = [&](const auto& conditions) {
            vector<vector<int>> adj(k);
            vector<int> in_degree(k);
            for (const auto& c : conditions) {
                const int u = c[0] - 1, v = c[1] - 1;
                adj[u].emplace_back(v);
                ++in_degree[v];
            }
            vector<int> result;
            vector<int> q;
            for (int u = 0; u < k; ++u) {
                if (!in_degree[u]) {
                    q.emplace_back(u);
                }
            }
            while (!empty(q)) {
                vector<int> new_q;
                for (const auto& u : q) {
                    result.emplace_back(u);
                    for (const auto& v : adj[u]) {
                        --in_degree[v];
                        if (in_degree[v]) {
                            continue;
                        }
                        new_q.emplace_back(v);
                    }
                }
                q = move(new_q);
            }
            return result;
        };

        const auto& row_order = topological_sort(rowConditions);
        if (size(row_order) != k) {
            return {};
        }
        const auto& col_order = topological_sort(colConditions);
        if (size(col_order) != k) {
            return {};
        }
        vector<int> row_idx(k);
        for (int i = 0; i < k; ++i) {
            row_idx[row_order[i]] = i;
        }
        vector<int> col_idx(k);
        for (int i = 0; i < k; ++i) {
            col_idx[col_order[i]] = i;
        }
        vector<vector<int>> result(k, vector<int>(k));
        for (int i = 0; i < k; ++i) {
            result[row_idx[i]][col_idx[i]] = i + 1;
        }
        return result;
    }

