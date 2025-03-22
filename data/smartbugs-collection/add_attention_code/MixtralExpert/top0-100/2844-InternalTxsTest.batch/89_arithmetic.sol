 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
