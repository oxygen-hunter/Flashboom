 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
