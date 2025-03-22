 

pragma solidity ^0.4.25;

contract TimedCrowdsale {
   

    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


  function isSaleFinished() view public returns (bool) {
     
    return block.timestamp >= 1546300800;
  }
}
