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


    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> cnt;
        int64_t result = 0;
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] != nums2[i]) {
                continue;
            }
            ++cnt[nums1[i]];
            result += i;
        }
        if (empty(cnt)) {
            return 0;
        }
        const int majority = max_element(cbegin(cnt), cend(cnt),
                                         [](const auto& a, const auto& b) {
                                                return a.second < b.second;
                                         })->first;
        int remain = cnt[majority] - (accumulate(cbegin(cnt), cend(cnt), 0,
                                                 [](const auto& total, const auto& x) {
                                                     return total + x.second;
                                                 }) - cnt[majority]);
        if (remain <= 0) {
            return result;
        }
        for (int i = 0; i < size(nums1); ++i) {
            if (nums1[i] == nums2[i] || nums1[i] == majority || nums2[i] == majority) {
                continue;
            }
            result += i;
            if (--remain == 0) {
                return result;
            }
        }
        return -1;
    }


