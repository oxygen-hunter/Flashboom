def prepare_plugin_docs_command(self, plugin_names, plugin_type=None, response_format=None,
                                snippet=False, playbook_dir=None, module_path=None):

    if response_format and response_format not in DocConfig._supported_response_formats:
        raise ConfigurationError("Invalid response_format {0}, valid value is one of either {1}".format(response_format,
                                                                                                        ", ".join(DocConfig._supported_response_formats)))

    if not isinstance(plugin_names, list):
        raise ConfigurationError("plugin_names should be of type list, instead received {0} of type {1}".format(plugin_names, type(plugin_names)))

    self._prepare_env(runner_mode=self.runner_mode)
    self.cmdline_args = []

    if response_format == 'json':
        self.cmdline_args.append('-j')

    if snippet:
        self.cmdline_args.append('-s')

    if plugin_type:
        self.cmdline_args.extend(['-t', plugin_type])

    if playbook_dir:
        self.cmdline_args.extend(['--playbook-dir', playbook_dir])

    if module_path:
        self.cmdline_args.extend(['-M', module_path])

    self.cmdline_args.append(" ".join(plugin_names))

    self.command = [self._ansible_doc_exec_path] + self.cmdline_args
    self._handle_command_wrap(self.execution_mode, self.cmdline_args)

def stoneGameV(self, stoneValue):
    """
    :type stoneValue: List[int]
    :rtype: int
    """
    n = len(stoneValue)
    prefix = [0]
    for v in stoneValue:
        prefix.append(prefix[-1] + v)

    mid = [[0]*n for _ in xrange(n)]
    for l in xrange(1, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = i if l == 1 else mid[i][j-1]
            while prefix[p]-prefix[i] < prefix[j+1]-prefix[p]:
                p += 1  # Time: O(n^2) in total
            mid[i][j] = p
    
    rmq = [[0]*n for _ in xrange(n)]
    for i in xrange(n):
        rmq[i][i] = stoneValue[i]

    dp = [[0]*n for _ in xrange(n)]
    for l in xrange(2, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = mid[i][j]
            max_score = 0
            if prefix[p]-prefix[i] == prefix[j+1]-prefix[p]:
                max_score = max(rmq[i][p-1], rmq[j][p])
            else:
                if i <= p-2:
                    max_score = max(max_score, rmq[i][p-2])
                if p <= j:
                    max_score = max(max_score, rmq[j][p])
            dp[i][j] = max_score
            rmq[i][j] = max(rmq[i][j-1], (prefix[j+1]-prefix[i]) + max_score)
            rmq[j][i] = max(rmq[j][i+1], (prefix[j+1]-prefix[i]) + max_score)
    return dp[0][n-1]


