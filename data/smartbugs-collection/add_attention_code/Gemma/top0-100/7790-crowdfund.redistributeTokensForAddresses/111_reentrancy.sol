 

pragma solidity ^0.4.19;

contract PERSONAL_BANK
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum = 1 ether;
    
    LogFile Log = LogFile(0x0486cF65A2F2F3A392CBEa398AFB7F5f0B72FF46);
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        if(intitalized)revert();
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        if(intitalized)revert();
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Deposit()
    public
    payable
    {
        balances[msg.sender]+= msg.value;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        if(balances[msg.sender]>=MinSum && balances[msg.sender]>=_am)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Deposit();
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
    assert(c >= a);
    return c;
  }
}

contract crowdfund {

    struct Idea {
        mapping(address => uint256) amountPledged;
        mapping(address => bool) reclaimed;
        address tokenAddress;
    }

    Idea[] public ideas;
    uint256 public FAILED_STATUS;
    
    event UserRegainedAmountAtIndex(address user,uint256 amount,uint256 index);

    function crowdfund() {
        FAILED_STATUS=4;
    }

    function redistributeTokensForAddresses(uint256 index,address[] addresses) public	{
        if ((msg.sender==ideas[index].creator) || (msg.sender==ideas[index].host))	{
            if (ideas[index].status==FAILED_STATUS)	{
                for(uint256 i = 0; i < addresses.length; i++) {
                    address addr=addresses[i];
                    if (!ideas[index].reclaimed[addr])    { 
                        uint256 reclaimAmount=ideas[index].amountPledged[addr];
                        if (reclaimAmount>0)    { 
                            ideas[index].reclaimed[addr]=true; 
                            emit UserRegainedAmountAtIndex(addr,reclaimAmount,index);
                            if(! token(ideas[index].tokenAddress).transfer(addr,reclaimAmount)) revert();
                        }
                    }
                }    
            }
        }
    }
}

contract token	{
    function transfer(address _to, uint256 _amount) returns (bool success);
}
