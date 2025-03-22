 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


  function transferCoins(address receiver) payable public {
    require(receiver != 0X0);
    require(msg.sender != receiver);
    require(msg.value > 0);
    receiver.transfer(msg.value);
  }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
