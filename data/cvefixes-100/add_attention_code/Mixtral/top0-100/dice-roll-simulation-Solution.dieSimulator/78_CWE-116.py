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

def dieSimulator(self, n, rollMax):
    """
    :type n: int
    :type rollMax: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def sum_mod(array):
        return reduce(lambda x, y: (x+y)%MOD, array)

    dp = [[1] + [0]*(rollMax[i]-1) for i in xrange(6)]  # 0-indexed
    for _ in xrange(n-1):
        new_dp = [[0]*rollMax[i] for i in xrange(6)]
        for i in xrange(6):
            for k in xrange(rollMax[i]):
                for j in xrange(6):
                    if i == j:
                        if k < rollMax[i]-1:  # 0-indexed
                            new_dp[j][k+1] = (new_dp[j][k+1]+dp[i][k])%MOD
                    else:
                        new_dp[j][0] = (new_dp[j][0]+dp[i][k])%MOD
        dp = new_dp
    return sum_mod(sum_mod(row) for row in dp)


