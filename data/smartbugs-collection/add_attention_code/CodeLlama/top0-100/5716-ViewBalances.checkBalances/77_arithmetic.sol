 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


    
  function checkBalances(address[] addresses) public constant returns(uint256[]){
      uint256[] storage balances;
      for(uint256 i = 0; i < addresses.length; i++){
          balances.push(addresses[i].balance);
      }
      return balances;
  }        


    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
