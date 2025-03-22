 

pragma solidity 0.4.25;

contract ReturnValue {


    function currentBlockHashCst() constant public returns (bytes32 b) {
        return blockhash(block.number); 
    }

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
