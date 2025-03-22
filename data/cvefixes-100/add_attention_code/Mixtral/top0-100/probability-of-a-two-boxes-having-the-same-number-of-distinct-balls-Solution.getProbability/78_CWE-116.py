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

def getProbability(self, balls):
    """
    :type balls: List[int]
    :rtype: float
    """
    def nCrs(n):  # Time: O(n), Space: O(1)
        c = 1
        for k in xrange(n+1):
            yield c
            c *= n-(k+1)+1
            c //= k+1
    
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    dp = collections.defaultdict(int)
    dp[0, 0] = 1  # dp[i, j] is the number of ways with number difference i and color difference j
    for n in balls:  # O(k) times
        new_dp = collections.defaultdict(int)
        for (ndiff, cdiff), count in dp.iteritems():  # O(k^2 * n) times
            for k, new_count in enumerate(nCrs(n)):  # O(n) times
                new_ndiff = ndiff+(k-(n-k))
                new_cdiff = cdiff-1 if k == 0 else (cdiff+1 if k == n else cdiff)
                new_dp[new_ndiff, new_cdiff] += count*new_count
        dp = new_dp
    total = sum(balls)
    return float(dp[0, 0])/nCr(total, total//2)


