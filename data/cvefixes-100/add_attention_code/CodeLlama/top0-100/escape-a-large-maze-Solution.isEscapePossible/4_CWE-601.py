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

def isEscapePossible(self, blocked, source, target):
    """
    :type blocked: List[List[int]]
    :type source: List[int]
    :type target: List[int]
    :rtype: bool
    """
    R, C = 10**6, 10**6
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(blocks, source, target):
        max_area_surrounded_by_blocks = len(blocks)*(len(blocks)-1)//2
        lookup = set([source])
        if len(lookup) > max_area_surrounded_by_blocks:
            return True
        q = collections.deque([source])
        while q:
            source = q.popleft()
            if source == target:
                return True
            for direction in directions:
                nr, nc = source[0]+direction[0], source[1]+direction[1]
                if not ((0 <= nr < R) and
                        (0 <= nc < C) and 
                        (nr, nc) not in lookup and
                        (nr, nc) not in blocks):
                    continue
                lookup.add((nr, nc))
                if len(lookup) > max_area_surrounded_by_blocks:
                    return True
                q.append((nr, nc))
        return False
    
    return bfs(set(map(tuple, blocked)), tuple(source), tuple(target)) and \
           bfs(set(map(tuple, blocked)), tuple(target), tuple(source))


