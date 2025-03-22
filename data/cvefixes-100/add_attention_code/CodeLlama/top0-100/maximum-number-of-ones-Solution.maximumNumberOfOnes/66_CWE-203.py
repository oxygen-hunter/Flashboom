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

def maximumNumberOfOnes(self, width, height, sideLength, maxOnes):
    """
    :type width: int
    :type height: int
    :type sideLength: int
    :type maxOnes: int
    :rtype: int
    """
    if width < height:
        width, height = height, width

    # 1. split matrix by SxS tiles
    # 2. split each SxS tile into four parts
    #    (r, c), (r, S-c), (S-r, c), (S-r, S-c)
    # 3. for each count of tile part in matrix is
    #    (R+1)*(C+1), (R+1)*C, R*(C+1), R*C (already in descending order)
    # 4. fill one into matrix by tile part of which count is in descending order
    #    until number of ones in a tile comes to maxOnes
    # 
    # ps. area of a tile and its count in matrix are as follows:
    #
    #  |<---- c ---->|<-- S-c -->|
    #  ^             |           |
    #  |             |           |
    #  r (R+1)*(C+1) |  (R+1)*C  |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #  ^             |           |
    #  |             |           |
    #  S-r  R*(C+1)  |   R*C     |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #

    R, r = divmod(height, sideLength)
    C, c = divmod(width, sideLength)
    assert(R <= C)
    area_counts = [(r*c, (R+1)*(C+1)), \
                   (r*(sideLength-c), (R+1)*C), \
                   ((sideLength-r)*c, R*(C+1)), \
                   ((sideLength-r)*(sideLength-c), R*C)]
    result = 0
    for area, count in area_counts:
        area = min(maxOnes, area)
        result += count*area
        maxOnes -= area
        if not maxOnes:
            break
    return result


