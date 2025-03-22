def prepare(self, reactor, clock, hs):
    # build a replication server
    server_factory = ReplicationStreamProtocolFactory(hs)
    self.streamer = hs.get_replication_streamer()
    self.server = server_factory.buildProtocol(None)

    # Make a new HomeServer object for the worker
    self.reactor.lookups["testserv"] = "1.2.3.4"
    self.worker_hs = self.setup_test_homeserver(
        http_client=None,
        homeserver_to_use=GenericWorkerServer,
        config=self._get_worker_hs_config(),
        reactor=self.reactor,
    )

    # Since we use sqlite in memory databases we need to make sure the
    # databases objects are the same.
    self.worker_hs.get_datastore().db_pool = hs.get_datastore().db_pool

    self.test_handler = self._build_replication_data_handler()
    self.worker_hs._replication_data_handler = self.test_handler

    repl_handler = ReplicationCommandHandler(self.worker_hs)
    self.client = ClientReplicationStreamProtocol(
        self.worker_hs, "client", "test", clock, repl_handler,
    )

    self._client_transport = None
    self._server_transport = None

def countMatchingSubarrays(self, nums, pattern):
    """
    :type nums: List[int]
    :type pattern: List[int]
    :rtype: int
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j+1 > 0 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    def KMP(text, pattern):
        prefix = getPrefix(pattern)
        j = -1
        for i, x in enumerate(text):
            while j+1 > 0 and pattern[j+1] != x:
                j = prefix[j]
            if pattern[j+1] == x:
                j += 1
            if j+1 == len(pattern):
                yield i-j
                j = prefix[j]

    return sum(1 for _ in KMP((cmp(nums[i+1], nums[i]) for i in xrange(len(nums)-1)), pattern))


