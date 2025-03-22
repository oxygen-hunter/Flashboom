 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function zint_convert(string key) public pure returns (bytes32 ret) {
        if (bytes(key).length > 32) revert();
        assembly {
          ret := mload(add(key, 32))
        }
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
