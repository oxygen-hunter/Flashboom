def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def checkMove(self, board, rMove, cMove, color):
    """
    :type board: List[List[str]]
    :type rMove: int
    :type cMove: int
    :type color: str
    :rtype: bool
    """
    def check(board, color, r, c, dr, dc):
        l = 2
        while 0 <= r < len(board) and 0 <= c < len(board[0]) and board[r][c] != '.':
            if board[r][c] == color:
                return l >= 3    
            r += dr
            c += dc
            l += 1
        return False

    directions = [(0, -1), (0, 1), (-1, 0), (1, 0),
                  (-1, -1), (1, -1), (-1, 1), (1, 1)]
    for dr, dc in directions:
        r, c = rMove+dr, cMove+dc
        if check(board, color, r, c, dr, dc):
            return True
    return False


