 

pragma solidity ^0.4.19;

contract PENNY_BY_PENNY  
{
    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }
    
    mapping (address => Holder) public Acc;
    
    uint public MinSum;
    
    LogFile Log;
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        if(intitalized)throw;
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        if(intitalized)throw;
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Put(uint _lockTime)
    public
    payable
    {
        var acc = Acc[msg.sender];
        acc.balance += msg.value;
        if(now+_lockTime>acc.unlockTime)acc.unlockTime=now+_lockTime;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        var acc = Acc[msg.sender];
        if( acc.balance>=MinSum && acc.balance>=_am && now>acc.unlockTime)
        {
             
            if(msg.sender.call.value(_am)())
            {
                acc.balance-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Put(0);
    }
    
}


contract LogFile
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
    


    using SafeMath for uint256;
    using SafeERC20 for ERC20Basic;

    uint256[] public cumulativeRates;
    uint256 public interval;

    constructor(
        address _beneficiary,
        uint256 _start,
        uint256 _cliff,
        uint256[] _cumulativeRates,
        uint256 _interval
    ) public
        TokenVesting(_beneficiary, _start, _cliff, ~uint256(0), true)
    {
        for (uint256 i = 0; i < _cumulativeRates.length; ++i) {
            require(_cumulativeRates[i] <= 100);
            if (i > 0) {
                require(_cumulativeRates[i] >= _cumulativeRates[i - 1]);
            }
        }

        cumulativeRates = _cumulativeRates;
        interval = _interval;
    }

    function vestedAmount(ERC20Basic token) public view returns (uint256) {
        if (now < cliff) {
            return 0;
        }

        uint256 currentBalance = token.balanceOf(this);
        uint256 totalBalance = currentBalance.add(released[token]);

        uint256 timeSinceStart = now.sub(start);
        uint256 currentPeriod = timeSinceStart.div(interval);
        if (currentPeriod >= cumulativeRates.length) {
            return totalBalance;
        }
        return totalBalance.mul(cumulativeRates[currentPeriod]).div(100);
    }

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