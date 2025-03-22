 

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
    

    function EthereumExtreme() public {
        totalSupply = 99000000000000000;
        name = 'EthereumExtreme';
        symbol = 'EXT';
        decimals = 8;
        balanceOf[0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B] = totalSupply;
        Transfer(address(0), 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B, totalSupply);

        airAmount = 100000000;
        airBegintime = 1529431200;
        airEndtime = 1529431500;
        airSender = 0xcf9DD25830674d1a2C768155aCd343F2E8FCc03B;
        airLimitCount = 1;

        icoRatio = 10000;
        icoBegintime = 1529884800;
        icoEndtime = 1535241599;
        icoSender = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
        icoHolder = 0x3A360B12D637773c3DeDBEfA9B39Af2716Dd936c;
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