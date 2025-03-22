 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
