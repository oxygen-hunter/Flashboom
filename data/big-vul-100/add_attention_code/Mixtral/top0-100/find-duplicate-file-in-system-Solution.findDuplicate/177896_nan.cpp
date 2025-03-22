static void become_daemon(const char *pidfile)
{
#ifndef _WIN32
    pid_t pid, sid;

    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (pidfile) {
        if (!ga_open_pidfile(pidfile)) {
            g_critical("failed to create pidfile");
            exit(EXIT_FAILURE);
         }
     }
 
    umask(0);
     sid = setsid();
     if (sid < 0) {
         goto fail;
    }
    if ((chdir("/")) < 0) {
        goto fail;
    }

    reopen_fd_to_null(STDIN_FILENO);
    reopen_fd_to_null(STDOUT_FILENO);
    reopen_fd_to_null(STDERR_FILENO);
    return;

fail:
    if (pidfile) {
        unlink(pidfile);
    }
    g_critical("failed to daemonize");
    exit(EXIT_FAILURE);
#endif
}

    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> files;
        for (const auto& path : paths) {
    	    stringstream ss(path);
    	    string root;
    	    string s;
    	    getline(ss, root, ' ');
    	    while (getline(ss, s, ' ')) {
    		    auto fileName = root + '/' + s.substr(0, s.find('('));
    		    auto fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
    		    files[fileContent].emplace_back(fileName);
    	    }
        }
    
        vector<vector<string>> result;
        for (const auto& file : files) {
    	    if (file.second.size() > 1) {
    		    result.emplace_back(file.second);
    	    }
        }
        return result;
    }

