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

def shortestPath(self, grid, k):
    """
    :type grid: List[List[int]]
    :type k: int
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, t, k):
        f, dh = g(b, t), 2
        closer, detour = [(b, k)], []
        lookup = {}
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, k = closer.pop()
            if b == t:
                return f
            if b in lookup and lookup[b] >= k:
                continue
            lookup[b] = k
            for dx, dy in directions:
                nb = (b[0]+dx, b[1]+dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        (grid[nb[0]][nb[1]] == 0 or k > 0) and
                        (nb not in lookup or lookup[nb] < k)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, k-int(grid[nb[0]][nb[1]] == 1)))
        return -1

    return a_star(grid, (0, 0), (len(grid)-1, len(grid[0])-1), k)


