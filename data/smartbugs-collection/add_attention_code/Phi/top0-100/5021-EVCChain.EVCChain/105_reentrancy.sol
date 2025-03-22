 

pragma solidity ^0.4.19;

contract MONEY_BOX   
{
    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }
    
    mapping (address => Holder) public Acc;
    
    uint public MinSum;
    
    Log LogFile;
    
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
        LogFile = Log(_log);
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
        LogFile.AddMessage(msg.sender,msg.value,"Put");
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
                LogFile.AddMessage(msg.sender,_am,"Collect");
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
library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  /**
   * @dev Constructor that gives msg.sender all of existing tokens.
   */
  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;

    //Investors 32%
    balances[0x5456118857653C15CFC5c42aFBA128eF198e2feB] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x5456118857653C15CFC5c42aFBA128eF198e2feB, 320000000 * (10 ** uint256(decimals)));

    //Fundation 48% 
    balances[0xaa98eb0cb8389b118995aad028a28ca3f53923d3] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xaa98eb0cb8389b118995aad028a28ca3f53923d3, 480000000 * (10 ** uint256(decimals)));

    //Core Team 20%
    balances[0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa, 200000000 * (10 ** uint256(decimals)));
  }

}
