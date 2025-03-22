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

    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        static const double EPS = 1e-15;
        static const int MOD = 1e9 + 7;
        const auto& powmod = [&](int a, int b) {
            a %= MOD;
            int64_t result = 1;
            while (b) {
                if (b & 1) {
                    result = result * a % MOD;
                }
                a = int64_t(a) * a % MOD;
                b >>= 1;
            }
            return result;
        };

        const auto& binary_search_right = [](auto left, auto right, const auto& check) {
            while (left <= right) {
                const auto mid = left + (right - left) / 2;
                if (!check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return right;
        };

        const auto& count = [](const auto& x, int target) {
            return static_cast<int>(target - x + EPS);
        };

        if (multiplier == 1) {
            return nums;
        }
        using P = pair<double, int>;
        vector<P> vals;
        for (int i = 0; i < size(nums); ++i) {
            vals.emplace_back(log(nums[i]) / log(multiplier), i);
        }
        sort(begin(vals), end(vals));
        const auto& check = [&](const auto& target) {
            int result = 0;
            for (const auto& [x, i] : vals) {
                const int c = count(x, target);
                if (c <= 0) {
                    break;
                }
                result += c;
            }
            return result <= k;
        };

        const int target = binary_search_right(1, static_cast<int>(vals.back().first) + 1, check);
        vector<int64_t> nums2(cbegin(nums), cend(nums));
        for (int idx = 0; idx < size(vals); ++idx) {
            const auto& [x, i] = vals[idx];
            const int c = count(x, target);
            if (c <= 0) {
                break;
            }
            k -= c;
            nums2[i] *= pow(multiplier, c);
        }
        using P2 = pair<int64_t, int>;
        vector<P2> vals2;
        for (int i = 0; i < size(nums2); ++i) {
            vals2.emplace_back(nums2[i], i);
        }
        sort(begin(vals2), end(vals2));
        const int q = k / size(nums), r = k % size(nums);
        const int m = powmod(multiplier, q);
        vector<int> result(size(nums));
        for (int idx = 0; idx < size(vals2); ++idx) {
            const auto& [x, i] = vals2[idx];
            result[i] = ((x % MOD * m) % MOD * (idx < r ? multiplier : 1)) % MOD;
        }
        return result;
    }

