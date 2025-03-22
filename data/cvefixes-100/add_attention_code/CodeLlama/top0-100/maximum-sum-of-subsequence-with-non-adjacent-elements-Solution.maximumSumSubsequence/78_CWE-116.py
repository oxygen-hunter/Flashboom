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

def maximumSumSubsequence(self, nums, queries):
    """
    :type nums: List[int]
    :type queries: List[List[int]]
    :rtype: int
    """
    MOD = 10**9+7
    L0R0, L1R0, L0R1, L1R1 = range(4)
    # Template:
    # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/block-placement-queries.py
    class SegmentTree(object):
        def __init__(self, N,
                    build_fn=lambda _: None,
                    query_fn=lambda x, y: y if x is None else x if y is None else max(x, y),
                    update_fn=lambda x: x):
            self.tree = [None]*(1<<((N-1).bit_length()+1))
            self.base = len(self.tree)>>1
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(h)
            while x > 1:
                x >>= 1
                self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])

        def query(self, L, R):
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L >>= 1
                R >>= 1
            return self.query_fn(left, right)
    
    def build(i):
        return [max(nums[i], 0), 0, 0, 0]
    
    def query(x, y):
        if x is None:
            return y
        if y is None:
            return x
        return [max(x[L0R1]+y[L1R0], x[L0R0]+y[L1R0], x[L0R1]+y[L0R0]),
                max(x[L1R1]+y[L1R0], x[L1R0]+y[L1R0], x[L1R1]+y[L0R0]),
                max(x[L0R1]+y[L1R1], x[L0R0]+y[L1R1], x[L0R1]+y[L0R1]),
                max(x[L1R1]+y[L1R1], x[L1R0]+y[L1R1], x[L1R1]+y[L0R1])]

    st = SegmentTree(len(nums), build_fn=build, query_fn=query)
    result = 0
    for i, x in queries:
        st.update(i, [max(x, 0), 0, 0, 0])
        result = (result+max(st.tree[1]))%MOD
    return result


