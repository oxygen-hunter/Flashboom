 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function zint_convert(string key) public pure returns (bytes32 ret) {
        if (bytes(key).length > 32) revert();
        assembly {
          ret := mload(add(key, 32))
        }
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
