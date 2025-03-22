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

def minimumOperations(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    even_top = collections.Counter(nums[i] for i in xrange(0, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    odd_top = collections.Counter(nums[i] for i in xrange(1, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    if not odd_top or even_top[0][0] != odd_top[0][0]:
        return len(nums)-even_top[0][1]-(odd_top[0][1] if odd_top else 0)
    return min(len(nums)-even_top[0][1]-(odd_top[1][1] if len(odd_top) == 2 else 0),
               len(nums)-odd_top[0][1]-(even_top[1][1] if len(even_top) == 2 else 0))


