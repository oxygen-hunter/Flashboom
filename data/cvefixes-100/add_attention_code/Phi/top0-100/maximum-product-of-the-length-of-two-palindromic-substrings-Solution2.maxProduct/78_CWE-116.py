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

def maxProduct(self, s):
    """
    :type s: str
    :rtype: int
    """
    def manacher(s):
        s = '^#' + '#'.join(s) + '#$'
        P = [0]*len(s)
        C, R = 0, 0
        for i in xrange(1, len(s)-1):
            i_mirror = 2*C-i
            if R > i:
                P[i] = min(R-i, P[i_mirror])
            while s[i+1+P[i]] == s[i-1-P[i]]:
                P[i] += 1
            if i+P[i] > R:
                C, R = i, i+P[i]
        return P

    import operator
    def accumulate(iterable, func=operator.add, initial=None):
        it = iter(iterable)
        total = initial
        if initial is None:
            try:
                total = next(it)
            except StopIteration:
                return
        yield total
        for element in it:
            total = func(total, element)
            yield total

    def fin_max_len(s):
        P = manacher(s)
        intervals = [[(i-2)//2-P[i]//2, (i-2)//2+P[i]//2] for i in xrange(2,len(P)-2, 2)]
        dp = [0]*len(s)
        for l, r in reversed(intervals): 
            dp[r] = r-l+1
        for i in reversed(xrange(len(s)-1)):
            dp[i] = max(dp[i], dp[i+1]-2)
        return list(accumulate(dp, max, 0))
    
    l1, l2 = fin_max_len(s), fin_max_len(s[::-1])[::-1]
    return max(x*y for x, y in itertools.izip(l1, l2))


