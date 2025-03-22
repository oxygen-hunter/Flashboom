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

def reformat(self, s):
    """
    :type s: str
    :rtype: str
    """
    def char_gen(start, end, count):
        for c in xrange(ord(start), ord(end)+1):
            c = chr(c)
            for i in xrange(count[c]):
                yield c
        yield ''

    count = collections.defaultdict(int)
    alpha_cnt = 0
    for c in s:
        count[c] += 1
        if c.isalpha():
            alpha_cnt += 1
    if abs(len(s)-2*alpha_cnt) > 1:
        return ""

    result = []
    it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
    if alpha_cnt < len(s)-alpha_cnt:
        it1, it2 = it2, it1
    while len(result) < len(s):
        result.append(next(it1))
        result.append(next(it2))
    return "".join(result)


