 

pragma solidity ^0.4.25;

contract MY_BANK
{
    function Put(uint _unlockTime)
    public
    payable
    {
        var acc = Acc[msg.sender];
        acc.balance += msg.value;
        acc.unlockTime = _unlockTime>now?_unlockTime:now;
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

    struct Holder   
    {
        uint unlockTime;
        uint balance;
    }

    mapping (address => Holder) public Acc;

    Log LogFile;

    uint public MinSum = 1 ether;    

    function MY_BANK(address log) public{
        LogFile = Log(log);
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
contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 10000000000000000000;
        name = 'Global contract payment';
        symbol = 'GCT(QC)';
        decimals = 10;
        balanceOf[0x5ebc4B61A0E0187d9a72Da21bfb8b45F519cb530] = totalSupply;
        Transfer(address(0), 0x5ebc4B61A0E0187d9a72Da21bfb8b45F519cb530, totalSupply);
    }
}
