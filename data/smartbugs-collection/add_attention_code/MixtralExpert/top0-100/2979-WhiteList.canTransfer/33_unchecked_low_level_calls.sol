 

pragma solidity 0.4.25;

contract ReturnValue {



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
