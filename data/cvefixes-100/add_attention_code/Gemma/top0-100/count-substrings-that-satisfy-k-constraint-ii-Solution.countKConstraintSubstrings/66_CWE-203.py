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

def countKConstraintSubstrings(self, s, k, queries):
    """
    :type s: str
    :type k: int
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    def count(l):
        return (l+1)*l//2

    result = cnt = left = 0
    prefix = [0]*(len(s)+1)
    lookup = [-1]*len(s)
    for right in xrange(len(s)):
        cnt += int(s[right] == '1')
        while not (cnt <= k or (right-left+1)-cnt <= k):
            cnt -= int(s[left] == '1')
            left += 1
        result += right-left+1
        prefix[right+1] = prefix[right]+(right-left+1)
        lookup[left] = right
    assert(lookup[0] != -1)
    for i in xrange(len(s)-1):
        if lookup[i+1] == -1:
            lookup[i+1] = lookup[i]
    return [count(min(lookup[left], right)-left+1)+(prefix[right+1]-prefix[min(lookup[left], right)+1]) for left, right in queries]


