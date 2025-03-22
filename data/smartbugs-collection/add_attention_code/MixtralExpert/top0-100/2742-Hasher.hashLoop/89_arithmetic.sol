 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function hashLoop(uint numTimes, bytes32 dataToHash) public returns (bytes32){
        for(uint i = 0 ; i < numTimes ; i++){
            dataToHash = keccak256(abi.encodePacked(dataToHash));
        }
        return dataToHash;
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
