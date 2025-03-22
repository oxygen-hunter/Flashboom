 

 pragma solidity ^0.4.15;

 contract Unprotected{
     address private owner;

     modifier onlyowner {
         require(msg.sender==owner);
         _;
     }


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

     function Unprotected()
         public
     {
         owner = msg.sender;
     }

      
      
     function changeOwner(address _newOwner)
         public
     {
        owner = _newOwner;
     }

     
 }
