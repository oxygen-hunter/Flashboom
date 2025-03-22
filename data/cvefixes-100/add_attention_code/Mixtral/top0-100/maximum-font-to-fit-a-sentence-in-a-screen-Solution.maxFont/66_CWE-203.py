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

def maxFont(self, text, w, h, fonts, fontInfo):
    """
    :type text: str
    :type w: int
    :type h: int
    :type fonts: List[int]
    :type fontInfo: FontInfo
    :rtype: int
    """
    def check(count, w, h, fonts, fontInfo, x):  # Time: O(1)
        return (fontInfo.getHeight(fonts[x]) <= h and
                sum(cnt * fontInfo.getWidth(fonts[x], c) for c, cnt in count.iteritems()) <= w)

    count = collections.Counter(text)
    left, right = 0, len(fonts)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(count, w, h, fonts, fontInfo, mid):
            right = mid-1
        else:
            left = mid+1
    return fonts[right] if right >= 0 else -1


