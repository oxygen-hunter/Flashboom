 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
