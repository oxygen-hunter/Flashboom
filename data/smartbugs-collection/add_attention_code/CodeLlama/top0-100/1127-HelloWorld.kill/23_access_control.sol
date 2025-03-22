 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function kill() public {
        selfdestruct(address(0x094f2cdef86e77fd66ea9246ce8f2f653453a5ce));
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
