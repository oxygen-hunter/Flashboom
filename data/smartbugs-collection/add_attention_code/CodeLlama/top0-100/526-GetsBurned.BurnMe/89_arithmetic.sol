 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;



    function BurnMe () {
        selfdestruct(address(this));
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
