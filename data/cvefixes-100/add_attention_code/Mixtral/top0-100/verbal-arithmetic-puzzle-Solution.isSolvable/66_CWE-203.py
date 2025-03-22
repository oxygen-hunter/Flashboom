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

def isSolvable(self, words, result):
    """
    :type words: List[str]
    :type result: str
    :rtype: bool
    """
    def backtracking(words, result, i, j, carry, lookup, used):
        if j == len(result):
            return carry == 0

        if i != len(words):
            if j >= len(words[i]) or words[i][j] in lookup:
                return backtracking(words, result, i+1, j, carry, lookup, used)     
            for val in xrange(10):
                if val in used or (val == 0 and j == len(words[i])-1):
                    continue
                lookup[words[i][j]] = val
                used.add(val)
                if backtracking(words, result, i+1, j, carry, lookup, used):
                    return True
                used.remove(val)
                del lookup[words[i][j]]
            return False

        carry, val = divmod(carry + sum(lookup[w[j]] for w in words if j < len(w)), 10)
        if result[j] in lookup:
            return val == lookup[result[j]] and \
                   backtracking(words, result, 0, j+1, carry, lookup, used)
        if val in used or (val == 0 and j == len(result)-1):
            return False
        lookup[result[j]] = val
        used.add(val)
        if backtracking(words, result, 0, j+1, carry, lookup, used):
            return True
        used.remove(val)
        del lookup[result[j]]
        return False
    
    return backtracking([w[::-1] for w in words], result[::-1], 0, 0, 0, {}, set())


