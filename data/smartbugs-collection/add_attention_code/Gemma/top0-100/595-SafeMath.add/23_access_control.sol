 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   


    function add(uint a, uint b) internal pure returns (uint c) {
        c = a + b;
        require(c >= a);
    }


  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
