 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
