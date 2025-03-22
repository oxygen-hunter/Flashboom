 

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


    function BitcoinBrand() public {
        totalSupply = 30000000000000000000000000000;
        name = 'BitcoinBrand';
        symbol = 'BTCB';
        decimals = 18;
        balanceOf[0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1] = totalSupply;
        Transfer(address(0), 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1, totalSupply);

        airAmount = 1000000000000000000;
        airBegintime = 1529956800;
        airEndtime = 1529957100;
        airSender = 0xc4e570D2644CCe3a71DC4345b13EE5FD3aF720d1;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1529971200;
        icoEndtime = 1535327940;
        icoSender = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
        icoHolder = 0xf46D665966674a8793aEd3109cCC65B2f638cF09;
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