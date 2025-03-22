def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

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


