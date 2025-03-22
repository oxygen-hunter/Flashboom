 

pragma solidity ^0.4.10;

contract Caller {


  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function callAddress(address a) {
         
        a.call();
    }
}