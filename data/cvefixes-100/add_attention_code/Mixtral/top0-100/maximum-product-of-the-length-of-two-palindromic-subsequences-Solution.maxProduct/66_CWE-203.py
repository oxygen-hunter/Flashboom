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

def maxProduct(self, s):
    """
    :type s: str
    :rtype: int
    """
    def palindromic_subsequence_length(s, mask):
        result = 0
        left, right = 0, len(s)-1
        left_bit, right_bit = 1<<left, 1<<right
        while left <= right:
            if mask&left_bit == 0:
                left, left_bit = left+1, left_bit<<1
            elif mask&right_bit == 0:
                right, right_bit = right-1, right_bit>>1
            elif s[left] == s[right]:
                result += 1 if left == right else 2
                left, left_bit = left+1, left_bit<<1
                right, right_bit = right-1, right_bit>>1
            else:
                return 0
        return result
    
    dp = [palindromic_subsequence_length(s, mask) for mask in xrange(1<<len(s))]
    result = 0
    for mask in xrange(len(dp)):
        if dp[mask]*(len(s)-dp[mask]) <= result:  # optimize
            continue
        # submask enumeration:
        # => sum(nCr(n, k) * 2^k for k in xrange(n+1)) = (1 + 2)^n = 3^n
        # => Time: O(3^n), see https://cp-algorithms.com/algebra/all-submasks.html
        submask = inverse_mask = (len(dp)-1)^mask
        while submask:
            result = max(result, dp[mask]*dp[submask])
            submask = (submask-1)&inverse_mask
    return result


