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

def earliestAndLatest(self, n, firstPlayer, secondPlayer):
    """
    :type n: int
    :type firstPlayer: int
    :type secondPlayer: int
    :rtype: List[int]
    """
    def memoization(t, l, r, lookup):
        # t: total number of players,
        # l: number of players left to the nearest top2 player,
        # r: number of players right to the nearest top2 player
        if (t, l, r) not in lookup:
            if l == r:
                return (1, 1)
            if l > r:  # make sure l <= r
                l, r, = r, l
            result = [float("inf"), 0]
            for i in xrange(l+1):
                l_win_cnt, l_lose_cnt, nt, pair_cnt = i+1, l-i, (t+1)//2, t//2
                min_j = max(l_lose_cnt, r-(pair_cnt-l_lose_cnt))  # j >= l_lose_cnt and j >= r-(pair_cnt-l_lose_cnt)
                max_j = min(r-l_win_cnt, (nt-l_win_cnt)-1)  # j <= r-l_win_cnt and j <= (nt-l_win_cnt)-1
                for j in xrange(min_j, max_j+1):
                    tmp = memoization(nt, i, j, lookup)
                    result = min(result[0], tmp[0]+1), max(result[1], tmp[1]+1)
            lookup[t, l, r] = result
        return lookup[t, l, r]
    
    return memoization(n, firstPlayer-1, n-secondPlayer, {})


