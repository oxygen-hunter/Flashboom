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

def differenceOfDistinctValues(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[List[int]]
    """
    def update(i, j):
        lookup = set()
        for k in xrange(min(len(grid)-i, len(grid[0])-j)):
            result[i+k][j+k] = len(lookup)
            lookup.add(grid[i+k][j+k])
        lookup.clear()
        for k in reversed(xrange(min(len(grid)-i, len(grid[0])-j))):
            result[i+k][j+k] = abs(result[i+k][j+k]-len(lookup))
            lookup.add(grid[i+k][j+k])

    result = [[0]*len(grid[0]) for _ in xrange(len(grid))]
    for j in xrange(len(grid[0])):
        update(0, j)
    for i in xrange(1, len(grid)):
        update(i, 0)
    return result


