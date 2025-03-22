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

def numWays(self, steps, arrLen):
    """
    :type steps: int
    :type arrLen: int
    :rtype: int
    """
    MOD = int(1e9+7)
    l = min(1+steps//2, arrLen)
    dp = [0]*(l+2)
    dp[1] = 1
    while steps > 0:
        steps -= 1
        new_dp = [0]*(l+2)
        for i in xrange(1, l+1):
            new_dp[i] = (dp[i] + dp[i-1] + dp[i+1]) % MOD
        dp = new_dp
    return dp[1]


