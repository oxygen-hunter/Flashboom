async def send_transactions(self, account, calls, nonce=None, max_fee=0):
    if nonce is None:
        execution_info = await account.get_nonce().call()
        nonce, = execution_info.result

    build_calls = []
    for call in calls:
        build_call = list(call)
        build_call[0] = hex(build_call[0])
        build_calls.append(build_call)

    (call_array, calldata, sig_r, sig_s) = self.signer.sign_transaction(hex(account.contract_address), build_calls, nonce, max_fee)
    return await account.__execute__(call_array, calldata, nonce).invoke(signature=[sig_r, sig_s])

def hasValidPath(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    E, S, W, N = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    directions = [
        [W, E], [N, S],
        [W, S], [S, E],
        [W, N], [N, E]
    ]

    for r, c in directions[grid[0][0]-1]:
        if not (0 <= r < len(grid) and 0 <= c < len(grid[0])):
            continue
        pr, pc = 0, 0
        while r != len(grid)-1 or c != len(grid[0])-1:
            for dx, dy in directions[grid[r][c]-1]:
                nr, nc = r+dx, c+dy
                if (nr == pr and nc == pc) or \
                   not(0 <= nr < len(grid) and 0 <= nc < len(grid[0])) or \
                   (-dx, -dy) not in directions[grid[nr][nc]-1]:
                    continue
                pr, pc, r, c = r, c, nr, nc
                break
            else:
                return False
        return True
    return len(grid) == len(grid[0]) == 1 


