 

pragma solidity ^0.4.19;

contract PRIVATE_ETH_CELL
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum;
    
    LogFile Log;
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        require(!intitalized);
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        require(!intitalized);
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
    

{
    struct Payer 
    {
        address ETHaddress;
        uint ETHamount;
    }

    Payer[] public persons;

    uint public paymentqueue = 0;
    uint amount;
    
    address meg = this;

    function canPay() internal                                                  
    {
        uint percent=110;  //if tx <0.05 ether - get 110%
        if (persons[paymentqueue].ETHamount > (1 ether)/20) //if tx > 0.05 ether - get 115%
        {
            percent =115;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/10) //if tx > 0.1 ether - get 120%
        {
            percent = 120;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/5)  //if tx >0.2 ether - get 125%
        {
            percent = 125;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/4)  //if tx > 0.25 ether - get 130%
        {
            percent = 130;
        }
        else if (persons[paymentqueue].ETHamount > (1 ether)/2)   //if tx > 0.5 ether - get 140%
        {
            percent = 140;
        }
        else if (persons[paymentqueue].ETHamount > ((1 ether)/2 + (1 ether)/4))  // if tx > 0.75 ether - get 145%
        {
            percent = 145;
        }
        while (meg.balance > persons[paymentqueue].ETHamount/100*percent)             
        {
            uint transactionAmount = persons[paymentqueue].ETHamount/100*percent;     
            persons[paymentqueue].ETHaddress.send(transactionAmount);           
            paymentqueue += 1;                                                    
        }
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