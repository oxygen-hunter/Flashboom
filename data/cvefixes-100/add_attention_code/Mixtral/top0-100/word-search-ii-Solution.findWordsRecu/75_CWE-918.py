def _delete_user(content):
    if ub.session.query(ub.User).filter(ub.User.role.op('&')(constants.ROLE_ADMIN) == constants.ROLE_ADMIN,
                                        ub.User.id != content.id).count():
        if content.name != "Guest":
            # Delete all books in shelfs belonging to user, all shelfs of user, downloadstat of user, read status
            # and user itself
            ub.session.query(ub.ReadBook).filter(content.id == ub.ReadBook.user_id).delete()
            ub.session.query(ub.Downloads).filter(content.id == ub.Downloads.user_id).delete()
            for us in ub.session.query(ub.Shelf).filter(content.id == ub.Shelf.user_id):
                ub.session.query(ub.BookShelf).filter(us.id == ub.BookShelf.shelf).delete()
            ub.session.query(ub.Shelf).filter(content.id == ub.Shelf.user_id).delete()
            ub.session.query(ub.Bookmark).filter(content.id == ub.Bookmark.user_id).delete()
            ub.session.query(ub.User).filter(ub.User.id == content.id).delete()
            ub.session.query(ub.ArchivedBook).filter(ub.ArchivedBook.user_id == content.id).delete()
            ub.session.query(ub.RemoteAuthToken).filter(ub.RemoteAuthToken.user_id == content.id).delete()
            ub.session.query(ub.User_Sessions).filter(ub.User_Sessions.user_id == content.id).delete()
            ub.session.query(ub.KoboSyncedBooks).filter(ub.KoboSyncedBooks.user_id == content.id).delete()
            # delete KoboReadingState and all it's children
            kobo_entries = ub.session.query(ub.KoboReadingState).filter(ub.KoboReadingState.user_id == content.id).all()
            for kobo_entry in kobo_entries:
                ub.session.delete(kobo_entry)
            ub.session_commit()
            log.info(u"User {} deleted".format(content.name))
            return(_(u"User '%(nick)s' deleted", nick=content.name))
        else:
            log.warning(_(u"Can't delete Guest User"))
            raise Exception(_(u"Can't delete Guest User"))
    else:
        log.warning(u"No admin user remaining, can't delete user")
        raise Exception(_(u"No admin user remaining, can't delete user"))

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


