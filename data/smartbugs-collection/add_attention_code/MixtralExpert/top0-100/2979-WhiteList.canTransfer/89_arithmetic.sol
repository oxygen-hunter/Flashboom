 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
