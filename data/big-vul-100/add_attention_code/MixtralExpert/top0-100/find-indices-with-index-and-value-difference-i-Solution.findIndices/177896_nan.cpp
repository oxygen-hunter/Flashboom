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


    vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
        for (int i = 0, mx_i = 0, mn_i = 0; i + indexDifference < size(nums); ++i) {
            if (nums[i] > nums[mx_i]) {
                mx_i = i;
            } else if (nums[i] < nums[mn_i]) {
                mn_i = i;
            }
            // we don't need to add abs for the difference since
            // - if nums[mx_i]-nums[i+indexDifference] < 0, then checking nums[i+indexDifference]-nums[mn_i] >= -(nums[mx_i]-nums[i+indexDifference]) > 0 can cover the case
            // - if nums[i+indexDifference]-nums[mn_i] < 0, then checking nums[mx_i]-nums[i+indexDifference] >= -(nums[i+indexDifference]-nums[mn_i]) > 0 can cover the case
            if (nums[mx_i] - nums[i + indexDifference] >= valueDifference) {
                return {mx_i, i + indexDifference};
            }
            if (nums[i + indexDifference] - nums[mn_i] >= valueDifference) {
                return {mn_i, i + indexDifference};
            }
        }
        return {-1, -1};
    }


