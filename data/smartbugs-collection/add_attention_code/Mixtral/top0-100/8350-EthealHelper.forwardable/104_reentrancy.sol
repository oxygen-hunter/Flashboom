 

pragma solidity ^0.4.24;

contract Reentrancy_bonus{

     
    mapping (address => uint) private userBalances;
    mapping (address => bool) private claimedBonus;
    mapping (address => uint) private rewardsForA;

    function withdrawReward(address recipient) public {
        uint amountToWithdraw = rewardsForA[recipient];
        rewardsForA[recipient] = 0;
        (bool success, ) = recipient.call.value(amountToWithdraw)("");
        require(success);
    }

    function getFirstWithdrawalBonus(address recipient) public {
        require(!claimedBonus[recipient]);  

        rewardsForA[recipient] += 100;
         
        withdrawReward(recipient);  
        claimedBonus[recipient] = true;
    }
}

contract iWhitelist {
    mapping(address => bool) public isWhitelisted;
}

contract iDeposit {
    uint256 public transactionCount;
    mapping (uint256 => Deposit) public transactions;
    iWhitelist public whitelist;
}

contract EthealHelper {
    function getTx(address _deposit, uint256 i) view public returns (uint256 amount, address beneficiary, uint64 time, bool cleared) {
        return iDeposit(_deposit).transactions(i);
    }
    
    function forwardable(address _deposit) view external returns (uint256[] ids) {
        iDeposit deposit = iDeposit(_deposit);
        uint256 _a = 0;
        address _b = 0x0;
        uint256 _t = 0;
        bool _c = false;
        uint256 i = 0;
        uint256 results = 0;
        uint256 txs = deposit.transactionCount();
        uint256[] memory _ids = new uint256[](txs);

        for (i = 0; i < txs; i++) {
            (_a, _b, _t, _c) = getTx(_deposit, i);
            if (!_c && deposit.whitelist().isWhitelisted(_b)) {
                _ids[results] = i;
                results++;
            }
        }

        ids = new uint256[](results);
        for (i = 0; i < results; i++) {
            ids[i] = _ids[i];
        }

        return ids;
    }
}
