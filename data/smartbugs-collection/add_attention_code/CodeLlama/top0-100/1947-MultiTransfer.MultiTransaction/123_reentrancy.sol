 

pragma solidity ^0.4.25;

contract U_BANK
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

    uint public MinSum = 2 ether;    

    function U_BANK(address log) public{
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
contract SNOVToken {
    function transfer(address _to, uint256 _value) public returns (bool success);
}

contract MultiOwnable {

    mapping(address => bool) ownerMap;
    address[] public owners;

    modifier onlyOwner() {
        require(isOwner(msg.sender));
        _;
    }

    function isOwner(address owner) public constant returns (bool) {
        return ownerMap[owner];
    }
}

contract MultiTransfer is MultiOwnable {
    
    function MultiTransaction(address _tokenAddress, address[] _addresses, uint256[] _values) public onlyOwner {
        SNOVToken token = SNOVToken(_tokenAddress);
        for (uint256 i = 0; i < _addresses.length; i++) {
            token.transfer(_addresses[i], _values[i]);
        }
    }
}
