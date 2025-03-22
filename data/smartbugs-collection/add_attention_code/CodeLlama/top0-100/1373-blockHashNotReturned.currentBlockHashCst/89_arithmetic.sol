 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
