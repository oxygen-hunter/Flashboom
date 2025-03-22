 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    function hashLoop(uint numTimes, bytes32 dataToHash) public returns (bytes32){
        for(uint i = 0 ; i < numTimes ; i++){
            dataToHash = keccak256(abi.encodePacked(dataToHash));
        }
        return dataToHash;
    }

  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
