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

def areSentencesSimilar(self, sentence1, sentence2):
    """
    :type sentence1: str
    :type sentence2: str
    :rtype: bool
    """
    if len(sentence1) > len(sentence2):
        sentence1, sentence2 = sentence2, sentence1
    count = 0
    for idx in (lambda x:x, lambda x:-1-x):
        for i in xrange(len(sentence1)+1):
            c1 = sentence1[idx(i)] if i != len(sentence1) else ' '
            c2 = sentence2[idx(i)] if i != len(sentence2) else ' '
            if c1 != c2:
                break
            if c1 == ' ':
                count += 1
    return count >= sentence1.count(' ')+1


