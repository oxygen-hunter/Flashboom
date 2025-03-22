 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


    function run(uint256 input) public {
         
        count *= input;
    }
}
