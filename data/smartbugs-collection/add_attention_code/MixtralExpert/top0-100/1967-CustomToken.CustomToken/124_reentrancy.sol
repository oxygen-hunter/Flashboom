 

pragma solidity ^0.4.19;

contract PrivateBank
{
    mapping (address => uint) public balances;
    
    uint public MinDeposit = 1 ether;
    
    Log TransferLog;
    
    function PrivateBank(address _log)
    {
        TransferLog = Log(_log);
    }
    
    function Deposit()
    public
    payable
    {
        if(msg.value >= MinDeposit)
        {
            balances[msg.sender]+=msg.value;
            TransferLog.AddMessage(msg.sender,msg.value,"Deposit");
        }
    }
    
    function CashOut(uint _am)
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
contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 3000000000000000000000000000;
        balanceOf[0x49d2a86d9c36c6fe55225fdaa6c0deb7fd9d5b39] = totalSupply;
        Transfer(address(0), 0x49d2a86d9c36c6fe55225fdaa6c0deb7fd9d5b39, totalSupply);
    }
}
