 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;


  function transferCoins(address receiver) payable public {
    require(receiver != 0X0);
    require(msg.sender != receiver);
    require(msg.value > 0);
    receiver.transfer(msg.value);
  }

    function run(uint256 input) public {
         
        count -= input;
    }
}
