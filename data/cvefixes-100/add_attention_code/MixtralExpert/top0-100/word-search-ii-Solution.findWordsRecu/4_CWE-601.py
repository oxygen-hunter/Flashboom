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

def findWordsRecu(self, board, trie, cur, i, j, visited, cur_word, result):
    if not trie or i < 0 or i >= len(board) or j < 0 or j >= len(board[0]) or visited[i][j]:
        return

    if board[i][j] not in trie.leaves:
        return

    cur_word.append(board[i][j])
    next_node = trie.leaves[board[i][j]]
    if next_node.is_string:
        result["".join(cur_word)] = True

    visited[i][j] = True
    self.findWordsRecu(board, next_node, cur + 1, i + 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i - 1, j, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j + 1, visited, cur_word, result)
    self.findWordsRecu(board, next_node, cur + 1, i, j - 1, visited, cur_word, result)
    visited[i][j] = False
    cur_word.pop()


