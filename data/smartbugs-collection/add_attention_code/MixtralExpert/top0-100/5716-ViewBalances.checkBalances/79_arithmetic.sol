 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
