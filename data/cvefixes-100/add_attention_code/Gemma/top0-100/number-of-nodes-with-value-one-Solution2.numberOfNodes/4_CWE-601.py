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

def numberOfNodes(self, n, queries):
    """
    :type n: int
    :type queries: List[int]
    :rtype: int
    """
    def iter_dfs():
        result = 0
        stk = [(1, 0)]
        while stk:
            u, curr = stk.pop()
            curr ^= cnt[u]%2
            result += curr
            for v in reversed(xrange(2*u, min(2*u+1, n)+1)):
                stk.append((v, curr))
        return result

    cnt = collections.Counter(queries)
    return iter_dfs()



