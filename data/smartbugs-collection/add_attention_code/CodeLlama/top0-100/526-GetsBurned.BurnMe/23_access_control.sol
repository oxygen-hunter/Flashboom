 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   


    function BurnMe () {
        selfdestruct(address(this));
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
