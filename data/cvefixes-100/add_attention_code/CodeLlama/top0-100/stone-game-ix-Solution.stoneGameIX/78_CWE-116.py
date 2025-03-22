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

def stoneGameIX(self, stones):
    """
    :type stones: List[int]
    :rtype: bool
    """
    count = collections.Counter(x%3 for x in stones)
    if count[0]%2 == 0:
        # iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
        # - assumed count[1] is the least one:
        #   1(,1,2)*,2,(,2)* => bob loses
        #            ^
        # - assumed count[2] is the least one:
        #   2(,2,1)*,1,(,1)* => bob loses
        #            ^
        return count[1] and count[2]
    # iff abs(count[1] - count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
    # - assumed count[1] is the most one
    #   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
    #                       ^
    #   1(,1,2)*,1,0,1,(,1)* => bob loses
    #                ^
    # - assumed count[2] is the most one
    #   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
    #                       ^
    #   2(,2,1)*,2,0,2,(,2)* => bob loses
    #                ^
    return abs(count[1]-count[2]) >= 3  


