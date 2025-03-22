 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;



    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
