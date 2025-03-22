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

def minNonZeroProduct(self, p):
    """
    :type p: int
    :rtype: int
    """
    MOD = 10**9+7

    # max_num = 2^p-1
    max_num_mod = (pow(2, p, MOD)-1)%MOD  # max_num % MOD

    # pair_product = max_num-1
    pair_product_mod = (max_num_mod-1)%MOD  # (max_num_mod-1) % MOD

    # since pair_product^MOD % MOD = pair_product_mod^MOD % MOD  = pair_product_mod
    # => pair_product_mod^(MOD-1) % MOD = 1
    # => pair_product_mod^(pair_cnt) % MOD = pair_product_mod^(pair_cnt%(MOD-1)) %MOD
    pair_cnt_mod_m_1 = (pow(2, p-1, MOD-1)-1) % (MOD-1)  # pair_cnt%(MOD-1)

    # the ans is:
    #   max_num * pair_product^pair_cnt % MOD
    # = max_num_mod * pair_product_mod^(pair_cnt_mod_m_1) % MOD
    return (max_num_mod*pow(pair_product_mod, pair_cnt_mod_m_1, MOD)) % MOD


