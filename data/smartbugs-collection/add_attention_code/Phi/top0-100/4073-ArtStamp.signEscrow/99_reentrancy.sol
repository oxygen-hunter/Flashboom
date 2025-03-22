 

pragma solidity ^0.4.19;

contract DEP_BANK 
{
    mapping (address=>uint256) public balances;   
   
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
    

contract ArtStamp { 
    
    struct Signature {
        address signee;
        bool hasSigned;
    }

    struct Escrow {
        Signature sender;
        Signature recipient;
        Signature witness;
        uint blockNum;
    }
    
    struct Piece {
        address owner;
        address witness;
    }

    mapping (uint => Escrow) escrowLedger;
    mapping (uint => Piece) pieces;

    function signEscrow(uint id) public {
        require(pieces[id].owner == address(this));

        require(msg.sender == escrowLedger[id].sender.signee ||
            msg.sender == escrowLedger[id].recipient.signee || 
            msg.sender == escrowLedger[id].witness.signee, 
            "You don't own this piece");

        bool allHaveSigned = true;

        if(msg.sender == escrowLedger[id].sender.signee){
            escrowLedger[id].sender.hasSigned = true;
        }  
        allHaveSigned = allHaveSigned && escrowLedger[id].sender.hasSigned;
        
        if(msg.sender == escrowLedger[id].recipient.signee){
            escrowLedger[id].recipient.hasSigned = true;
        }
        allHaveSigned = allHaveSigned && escrowLedger[id].recipient.hasSigned;
        
        if(msg.sender == escrowLedger[id].witness.signee){
            escrowLedger[id].witness.hasSigned = true;
        }        
        
        allHaveSigned = allHaveSigned && 
            (escrowLedger[id].witness.hasSigned || 
            escrowLedger[id].witness.signee == 0x0000000000000000000000000000000000000000);

        if(allHaveSigned)
        {
            address recipient = escrowLedger[id].recipient.signee;
            delete escrowLedger[id];
            pieces[id].owner = recipient;
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