 

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
pragma solidity ^0.4.24;

contract TCallee {
    function transferFrom(address _from, address _to, uint256 _value) external returns (bool success) {}
}

contract p2ptokenexchange {
    
    struct exchange {
        address one1;
        address smart1;
        uint256 amount1;
        address two2;
        address smart2;
        uint256 amount2;
        bool DealDone;
    }
    
    mapping (uint => exchange) exchanges;
    address constant atokenaddress = 0xf0B3BA2Dd4B2ef75d727A4045d7fBcc415B77bF0;
    event DoExchange (uint exchangeId);
    
    function doExchange (uint exchangeId) external payable returns (bool success) {
        bool _locked;
        require(!_locked);
        _locked = true;
        require(msg.value >= 206000000);
        if (exchanges[exchangeId].two2 != 0x1111111111111111111111111111111111111111) {
            require(msg.sender == exchanges[exchangeId].two2);
        } else {
            exchanges[exchangeId].two2 = msg.sender;
        }
   
        require(exchanges[exchangeId].DealDone == false);
        require(exchanges[exchangeId].amount2 > 0);
       
        if (exchanges[exchangeId].smart2 == address(0)) {
            require(msg.value >= 206000000 + exchanges[exchangeId].amount2);
            require(payether(atokenaddress, msg.value - exchanges[exchangeId].amount2) == true);
        } else {
            require(payether(atokenaddress, msg.value) == true);
        }

        if (exchanges[exchangeId].smart2 == address(0)) {
            require(payether(exchanges[exchangeId].one1, exchanges[exchangeId].amount2) == true);
        } else {
            TCallee c = TCallee(exchanges[exchangeId].smart2);
            bool x = c.transferFrom(exchanges[exchangeId].two2, exchanges[exchangeId].one1, exchanges[exchangeId].amount2);
            require(x == true);
        }

        if (exchanges[exchangeId].smart1 == address(0)) {
            require(payether(exchanges[exchangeId].two2, exchanges[exchangeId].amount1) == true);
        } else {
            TCallee d = TCallee(exchanges[exchangeId].smart1);
            bool y = d.transferFrom(exchanges[exchangeId].one1, exchanges[exchangeId].two2, exchanges[exchangeId].amount1);
            require(y == true);
        }
        
        exchanges[exchangeId].DealDone = true;
        emit DoExchange(exchangeId);
        _locked = false;
        return true;
    }

    function payether(address payto, uint256 amountTo) internal returns (bool) {
        payto.transfer(amountTo);
        return true;
    }
}
