 

 pragma solidity ^0.4.16;

contract Ethraffle_v4b {
    struct Contestant {
        address addr;
        uint raffleId;
    }

    event RaffleResult(
        uint raffleId,
        uint winningNumber,
        address winningAddress,
        address seed1,
        address seed2,
        uint seed3,
        bytes32 randHash
    );

    event TicketPurchase(
        uint raffleId,
        address contestant,
        uint number
    );

    event TicketRefund(
        uint raffleId,
        address contestant,
        uint number
    );

     
    uint public constant prize = 2.5 ether;
    uint public constant fee = 0.03 ether;
    uint public constant totalTickets = 50;
    uint public constant pricePerTicket = (prize + fee) / totalTickets;  
    address feeAddress;

     
    bool public paused = false;
    uint public raffleId = 1;
     
    uint public blockNumber = block.number;
    uint nextTicket = 0;
    mapping (uint => Contestant) contestants;
    uint[] gaps;

     

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




    function Ethraffle_v4b() public {
        feeAddress = msg.sender;
    }

     
    function () payable public {
        buyTickets();
    }

    function buyTickets() payable public {
        if (paused) {
            msg.sender.transfer(msg.value);
            return;
        }

        uint moneySent = msg.value;

        while (moneySent >= pricePerTicket && nextTicket < totalTickets) {
            uint currTicket = 0;
            if (gaps.length > 0) {
                currTicket = gaps[gaps.length-1];
                gaps.length--;
            } else {
                currTicket = nextTicket++;
            }

            contestants[currTicket] = Contestant(msg.sender, raffleId);
            TicketPurchase(raffleId, msg.sender, currTicket);
            moneySent -= pricePerTicket;
        }

         
        if (nextTicket == totalTickets) {
            chooseWinner();
        }

         
        if (moneySent > 0) {
            msg.sender.transfer(moneySent);
        }
    }

    function chooseWinner() private {
         
        address seed1 = contestants[uint(block.coinbase) % totalTickets].addr;
         
        address seed2 = contestants[uint(msg.sender) % totalTickets].addr;
         
        uint seed3 = block.difficulty;
        bytes32 randHash = keccak256(seed1, seed2, seed3);

        uint winningNumber = uint(randHash) % totalTickets;
        address winningAddress = contestants[winningNumber].addr;
        RaffleResult(raffleId, winningNumber, winningAddress, seed1, seed2, seed3, randHash);

         
        raffleId++;
        nextTicket = 0;
         
        blockNumber = block.number;

         
         
         

         
        winningAddress.transfer(prize);
        feeAddress.transfer(fee);
    }

     
    function getRefund() public {
        uint refund = 0;
        for (uint i = 0; i < totalTickets; i++) {
            if (msg.sender == contestants[i].addr && raffleId == contestants[i].raffleId) {
                refund += pricePerTicket;
                contestants[i] = Contestant(address(0), 0);
                gaps.push(i);
                TicketRefund(raffleId, msg.sender, i);
            }
        }

        if (refund > 0) {
            msg.sender.transfer(refund);
        }
    }

     
    function endRaffle() public {
        if (msg.sender == feeAddress) {
            paused = true;

            for (uint i = 0; i < totalTickets; i++) {
                if (raffleId == contestants[i].raffleId) {
                    TicketRefund(raffleId, contestants[i].addr, i);
                    contestants[i].addr.transfer(pricePerTicket);
                }
            }

            RaffleResult(raffleId, totalTickets, address(0), address(0), address(0), 0, 0);
            raffleId++;
            nextTicket = 0;
             
            blockNumber = block.number;
            gaps.length = 0;
        }
    }

    function togglePause() public {
        if (msg.sender == feeAddress) {
            paused = !paused;
        }
    }

    function kill() public {
        if (msg.sender == feeAddress) {
            selfdestruct(feeAddress);
        }
    }
}
