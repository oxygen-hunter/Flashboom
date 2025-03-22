 

pragma solidity ^0.4.15;

 
contract DosAuction {
  address currentFrontrunner;
  uint currentBid;

   

    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

  function bid() payable {
    require(msg.value > currentBid);

     
     
    if (currentFrontrunner != 0) {
       
       
      require(currentFrontrunner.send(currentBid));
    }

    currentFrontrunner = msg.sender;
    currentBid         = msg.value;
  }
}
