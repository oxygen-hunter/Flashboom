 

pragma solidity ^0.4.10;

contract Caller {

  function transferCoins(address receiver) payable public {
    require(receiver != 0X0);
    require(msg.sender != receiver);
    require(msg.value > 0);
    receiver.transfer(msg.value);
  }

    function callAddress(address a) {
         
        a.call();
    }
}