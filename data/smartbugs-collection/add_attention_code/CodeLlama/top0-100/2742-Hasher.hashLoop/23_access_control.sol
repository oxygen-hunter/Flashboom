 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function hashLoop(uint numTimes, bytes32 dataToHash) public returns (bytes32){
        for(uint i = 0 ; i < numTimes ; i++){
            dataToHash = keccak256(abi.encodePacked(dataToHash));
        }
        return dataToHash;
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
