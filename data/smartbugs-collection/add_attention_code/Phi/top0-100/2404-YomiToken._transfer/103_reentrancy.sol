 

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
library SafeMath {
    function sub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function add(uint256 a, uint256 b) internal pure returns (uint256) {
        uint256 c = a + b;
        assert(c >= a && c >= b);
        return c;
    }
}

contract YomiToken {
    using SafeMath for uint256;

    uint256 constant public teamReserve = 100000000e18;
    uint256 constant public foundationReserve = 200000000e18;
    uint256 public lockReleaseDate6Month;
    uint256 public lockReleaseDate1Year;
    address public teamAddr;
    address public foundationAddr;
    mapping (address => uint256) balances;
    mapping (address => bool) public frozenAccounts;
    
    event Transfer(address indexed _from, address indexed _to, uint256 _value);
    
    function _transfer(address _from, address _to, uint256 _value) internal {
        require(_to != 0x0);
        
        if (_from == teamAddr && now < lockReleaseDate6Month) {
            require(balances[_from].sub(_value) >= teamReserve);
        }
        
        if (_from == foundationAddr && now < lockReleaseDate1Year) {
            require(balances[_from].sub(_value) >= foundationReserve);
        }
        
        require(balances[_from] >= _value);
        require(balances[_to] + _value > balances[_to]);
        require(!frozenAccounts[_from]);
        require(!frozenAccounts[_to]);

        uint256 previousBalances = balances[_from].add(balances[_to]);
        balances[_from] = balances[_from].sub(_value);
        balances[_to] = balances[_to].add(_value);
        emit Transfer(_from, _to, _value);
        assert(balances[_from] + balances[_to] == previousBalances);
    }
}
