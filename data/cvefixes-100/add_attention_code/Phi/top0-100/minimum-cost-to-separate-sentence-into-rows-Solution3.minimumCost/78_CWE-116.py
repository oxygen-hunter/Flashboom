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

def minimumCost(self, sentence, k):
    """
    :type sentence: str
    :type k: int
    :rtype: int
    """
    word_lens = []
    j = 0
    for i in xrange(len(sentence)+1):
        if i != len(sentence) and sentence[i] != ' ':
            continue
        word_lens.append(i-j)
        j = i+1
    dp = [float("inf")]*(1+(len(word_lens)-1))  # dp[i]: min cost of the first i word_lens where i in [0, len(words)-1]
    dp[0] = 0
    for i in xrange(1, (len(word_lens)-1)+1):
        total = word_lens[i-1]
        for j in reversed(xrange(i)):
            dp[i] = min(dp[i], dp[j] + (k-total)**2)
            if j-1 < 0:
                continue
            total += (word_lens[j-1]+1)
            if total > k:
                break
    i, total = len(word_lens)-1, -1
    while i >= 0 and total + (word_lens[i]+1) <= k:  # find max i s.t. the length of the last line > k
        total += (word_lens[i]+1)
        i -= 1
    return min(dp[j] for j in xrange(i+1, len(dp)))


