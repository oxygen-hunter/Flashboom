 

pragma solidity 0.4.25;

contract ReturnValue {



    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}
