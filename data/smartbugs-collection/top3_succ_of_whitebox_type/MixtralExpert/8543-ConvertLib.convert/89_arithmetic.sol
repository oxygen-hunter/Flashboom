 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function convert(uint amount,uint conversionRate) public pure returns (uint convertedAmount) {
        return amount * conversionRate;
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
