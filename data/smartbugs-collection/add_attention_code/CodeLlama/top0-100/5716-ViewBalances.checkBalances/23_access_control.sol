 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
