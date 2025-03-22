 

pragma solidity ^0.4.10;

contract Caller {

    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


    function callAddress(address a) {
         
        a.call();
    }
}