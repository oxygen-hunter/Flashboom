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

def solve(self, board):
    """
    :type board: List[List[str]]
    :rtype: void Do not return anything, modify board in-place instead.
    """
    if not board:
        return

    q = collections.deque()

    for i in xrange(len(board)):
        if board[i][0] == 'O':
            board[i][0] = 'V'
            q.append((i, 0))
        if board[i][len(board[0])-1] == 'O':
            board[i][len(board[0])-1] = 'V'
            q.append((i, len(board[0])-1))

    for j in xrange(1, len(board[0])-1):
        if board[0][j] == 'O':
            board[0][j] = 'V'
            q.append((0, j))
        if board[len(board)-1][j] == 'O':
            board[len(board)-1][j] = 'V'
            q.append((len(board)-1, j))

    while q:
        i, j = q.popleft()
        for x, y in [(i+1, j), (i-1, j), (i, j+1), (i, j-1)]:
            if 0 <= x < len(board) and 0 <= y < len(board[0]) and \
               board[x][y] == 'O':
                board[x][y] = 'V'
                q.append((x, y))

    for i in xrange(len(board)):
        for j in xrange(len(board[0])):
            if board[i][j] != 'V':
                board[i][j] = 'X'
            else:
                board[i][j] = 'O'


