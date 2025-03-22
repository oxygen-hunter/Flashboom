/*
 * @source: etherscan.io 
 * @author: -
 * @vulnerable_at_lines: 52
 */

pragma solidity ^0.4.19;

contract benign_PrivateDeposit
{
    mapping (address => uint) public balances;
        
    uint public MinDeposit = 1 ether;
    address public owner;
    
    Log TransferLog;
    
    modifier onlyOwner() {
        require(tx.origin == owner);
        _;
    }    
    
    function benign_PrivateDeposit()
    {
        owner = msg.sender;
        TransferLog = new Log();
    }
    
    
    
    function benign_setLog(address _lib) onlyOwner
    {
        TransferLog = Log(_lib);
    }    
    
    function benign_Deposit()
    public
    payable
    {
        if(msg.value >= MinDeposit)
        {
            balances[msg.sender]+=msg.value;
            TransferLog.benign_AddMessage(msg.sender,msg.value,"benign_Deposit");
        }
    }
    
    function benign_CashOut(uint _am)
    {
        if(_am<=balances[msg.sender])
        {            
            // <yes> <report> REENTRANCY
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                TransferLog.benign_AddMessage(msg.sender,_am,"benign_CashOut");
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
    
    function benign_AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}