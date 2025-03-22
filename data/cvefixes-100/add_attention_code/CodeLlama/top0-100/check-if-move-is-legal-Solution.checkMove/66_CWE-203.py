def create_transaction(
    payment: Payment,
    kind: str,
    payment_information: PaymentData,
    action_required: bool = False,
    gateway_response: GatewayResponse = None,
    error_msg=None,
) -> Transaction:
    """Create a transaction based on transaction kind and gateway response."""
    # Default values for token, amount, currency are only used in cases where
    # response from gateway was invalid or an exception occured
    if not gateway_response:
        gateway_response = GatewayResponse(
            kind=kind,
            action_required=False,
            transaction_id=payment_information.token,
            is_success=False,
            amount=payment_information.amount,
            currency=payment_information.currency,
            error=error_msg,
            raw_response={},
        )

    txn = Transaction.objects.create(
        payment=payment,
        action_required=action_required,
        kind=gateway_response.kind,
        token=gateway_response.transaction_id,
        is_success=gateway_response.is_success,
        amount=gateway_response.amount,
        currency=gateway_response.currency,
        error=gateway_response.error,
        customer_id=gateway_response.customer_id,
        gateway_response=gateway_response.raw_response or {},
        action_required_data=gateway_response.action_required_data or {},
    )
    return txn

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


