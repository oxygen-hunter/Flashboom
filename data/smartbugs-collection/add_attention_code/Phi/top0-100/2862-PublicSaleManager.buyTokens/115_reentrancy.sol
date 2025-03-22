 

pragma solidity ^0.4.19;

contract ETH_VAULT
{
    mapping (address => uint) public balances;
    
    uint public MinDeposit = 1 ether;
    
    Log TransferLog;
    
    function ETH_VAULT(address _log)
    public 
    {
        TransferLog = Log(_log);
    }
    
    function Deposit()
    public
    payable
    {
        if(msg.value > MinDeposit)
        {
            balances[msg.sender]+=msg.value;
            TransferLog.AddMessage(msg.sender,msg.value,"Deposit");
        }
    }
    
    function CashOut(uint _am)
    public
    payable
    {
        if(_am<=balances[msg.sender])
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                TransferLog.AddMessage(msg.sender,_am,"CashOut");
            }
        }
    }
    
    function() public payable{}    
    
}

contract Log 
{
   
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    
    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}
contract ERC20 {
    function balanceOf(address tokenOwner) public constant returns (uint256 balance);
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    function owned() public { owner = msg.sender; }
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract PublicSaleManager is owned {

    mapping (address => bool) _earlyList;
    mapping (address => bool) _whiteList;
    mapping (address => uint256) _bonus;
    mapping (address => uint256) _contributedETH;

    address _tokenAddress = 0xAF815e887b039Fc06a8ddDcC7Ec4f57757616Cd2;
    uint256 _conversionRate = 0;
    uint256 _startTime = 0;

    uint256 _totalSold = 0;
    uint256 _totalBonus = 0;

    uint256 _regularPersonalCap = 1e20; // 100 ETH
    uint256 _higherPersonalCap = 2e20; // 200 ETH
    uint256 _minimumAmount = 2e17; // 0.2 ETH

    bool _is_stopped = false;

    function buyTokens() payable public {
        require(_is_stopped == false);

        // Validates whitelist.
        require(_whiteList[msg.sender] == true || _earlyList[msg.sender] == true);

        if (_earlyList[msg.sender]) {
            require(msg.value + _contributedETH[msg.sender] <= _higherPersonalCap);
        } else {
            require(msg.value + _contributedETH[msg.sender] <= _regularPersonalCap);
        }

        require(msg.value >= _minimumAmount);

        // Validates time.
        require(now > _startTime);
        require(now < _startTime + (31 days));

        // Calculates the purchase amount.
        uint256 purchaseAmount = msg.value * _conversionRate;
        require(_conversionRate > 0 && purchaseAmount / _conversionRate == msg.value);

        // Calculates the bonus amount.
        uint256 bonus = 0;
        if (_totalSold + purchaseAmount < 5e26) {
            // 10% bonus for the first 500 million OGT.
            bonus = purchaseAmount / 10;
        } else if (_totalSold + purchaseAmount < 10e26) {
            // 5% bonus for the first 1 billion OGT.
            bonus = purchaseAmount / 20;
        }

        // Checks that we still have enough balance.
        require(ERC20(_tokenAddress).balanceOf(this) >= _totalBonus + purchaseAmount + bonus);

        // Transfers the non-bonus part.
        ERC20(_tokenAddress).transfer(msg.sender, purchaseAmount);
        _contributedETH[msg.sender] += msg.value;

        // Records the bonus.
        _bonus[msg.sender] += bonus;

        _totalBonus += bonus;
        _totalSold += (purchaseAmount + bonus);
    }
}
