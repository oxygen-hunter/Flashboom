 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
