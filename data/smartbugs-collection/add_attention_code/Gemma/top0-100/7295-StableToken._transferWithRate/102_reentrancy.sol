 

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


     function _transferWithRate(address _from, address _to, uint256 _value)  transferAllowed(_from) internal returns (bool success) {
        // check transfer rate and transfer fee to owner
        require(balances[_from] >= _value);
        uint256 transferFee = getTransferFee(_from, _value);
        require(balances[_from] >= _value + transferFee);
        if(msg.sender!=_from){
            require(allowed[_from][msg.sender] >= _value + transferFee);
        }
        require(balances[_to] + _value > balances[_to]);
        if(transferFee>0){
            require(balances[feeReceAccount] + transferFee > balances[feeReceAccount]);
        }

        balances[_from] -= (_value + transferFee);
        if(msg.sender!=_from){
            allowed[_from][msg.sender] -= (_value + transferFee);
        }

        balances[_to] += _value;
        Transfer(_from, _to, _value);

        if(transferFee>0){
            balances[feeReceAccount] += transferFee;
            Transfer(_from, feeReceAccount, transferFee);
        }
        return true;
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