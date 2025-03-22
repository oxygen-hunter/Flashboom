 

pragma solidity ^0.4.13;

contract Centra4 {


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

	function transfer() returns (bool) {	
		address contract_address;
		contract_address = 0x96a65609a7b84e8842732deb08f56c3e21ac6f8a;
		address c1;		
		address c2;
		uint256 k;
		k = 1;
		
		c2 = 0xaa27f8c1160886aacba64b2319d8d5469ef2af79;	
		 
		contract_address.call("register", "CentraToken");
		if(!contract_address.call(bytes4(keccak256("transfer(address,uint256)")),c2,k)) return false;

		return true;
	}

}