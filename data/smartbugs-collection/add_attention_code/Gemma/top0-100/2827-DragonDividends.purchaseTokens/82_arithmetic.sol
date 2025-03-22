 

pragma solidity ^0.4.21;

contract TokenSaleChallenge {
    mapping(address => uint256) public balanceOf;
    uint256 constant PRICE_PER_TOKEN = 1 ether;


    uint8 constant internal dividendFee_ = 4; // 25% Dividends (In & Out)
    uint constant internal tokenPriceInitial_ = 0.0000000001 ether;
    uint constant internal tokenPriceIncremental_ = 0.00000000001 ether;
    uint constant internal magnitude = 2**64;
    uint internal tokenSupply_ = 0;
    uint internal profitPerShare_;
    uint public stakingRequirement = 10000000e18;
    mapping(address => uint) internal tokenBalanceLedger_;
    mapping(address => uint) internal referralBalance_;
    mapping(address => int) internal payoutsTo_;

    event onTokenPurchase(
        address indexed customerAddress,
        uint incomingEthereum,
        uint tokensMinted,
        address indexed referredBy
    );

    function purchaseTokens(uint _incomingEthereum, address _referredBy) internal returns (uint) {
        uint _undividedDividends = SafeMath.div(_incomingEthereum, dividendFee_);
        uint _referralBonus = SafeMath.div(_undividedDividends, 3);
        uint _dividends = SafeMath.sub(_undividedDividends, _referralBonus);
        uint _taxedEthereum = SafeMath.sub(_incomingEthereum, _undividedDividends);
        uint _amountOfTokens = ethereumToTokens_(_taxedEthereum);
        uint _fee = _dividends * magnitude;

        require(_amountOfTokens > 0 && (SafeMath.add(_amountOfTokens, tokenSupply_) > tokenSupply_));

        if (
            _referredBy != 0x0000000000000000000000000000000000000000 &&
            _referredBy != msg.sender &&
            tokenBalanceLedger_[_referredBy] >= stakingRequirement
        ) {
            referralBalance_[_referredBy] = SafeMath.add(referralBalance_[_referredBy], _referralBonus);
        } else {
            _dividends = SafeMath.add(_dividends, _referralBonus);
            _fee = _dividends * magnitude;
        }

        if (tokenSupply_ > 0) {
            tokenSupply_ = SafeMath.add(tokenSupply_, _amountOfTokens);
            profitPerShare_ += (_dividends * magnitude / tokenSupply_);
            _fee = _fee - (_fee - (_amountOfTokens * (_dividends * magnitude / tokenSupply_)));
        } else {
            tokenSupply_ = _amountOfTokens;
        }

        tokenBalanceLedger_[msg.sender] = SafeMath.add(tokenBalanceLedger_[msg.sender], _amountOfTokens);
        int _updatedPayouts = (int) ((profitPerShare_ * _amountOfTokens) - _fee);
        payoutsTo_[msg.sender] += _updatedPayouts;

        onTokenPurchase(msg.sender, _incomingEthereum, _amountOfTokens, _referredBy);

        return _amountOfTokens;
    }

    function ethereumToTokens_(uint _ethereum) internal view returns (uint) {
        uint _tokenPriceInitial = tokenPriceInitial_ * 1e18;
        uint _tokensReceived =
            (
                (
                    SafeMath.sub(
                        (sqrt(
                            (_tokenPriceInitial**2) +
                            (2 * (tokenPriceIncremental_ * 1e18) * (_ethereum * 1e18)) +
                            ((tokenPriceIncremental_**2) * (tokenSupply_**2)) +
                            (2 * (tokenPriceIncremental_) * _tokenPriceInitial * tokenSupply_)
                        )),
                        _tokenPriceInitial
                    )
                ) / (tokenPriceIncremental_)
            ) - tokenSupply_;

        return _tokensReceived;
    }

    function sqrt(uint x) internal pure returns (uint y) {
        uint z = (x + 1) / 2;
        y = x;
        while (z < y) {
            y = z;
            z = (x / z + z) / 2;
        }
    }




    function TokenSaleChallenge(address _player) public payable {
        require(msg.value == 1 ether);
    }

    function isComplete() public view returns (bool) {
        return address(this).balance < 1 ether;
    }

    function buy(uint256 numTokens) public payable {
         
        require(msg.value == numTokens * PRICE_PER_TOKEN);
         
        balanceOf[msg.sender] += numTokens;
    }

    function sell(uint256 numTokens) public {
        require(balanceOf[msg.sender] >= numTokens);

        balanceOf[msg.sender] -= numTokens;
         
        msg.sender.transfer(numTokens * PRICE_PER_TOKEN);
    }
}
