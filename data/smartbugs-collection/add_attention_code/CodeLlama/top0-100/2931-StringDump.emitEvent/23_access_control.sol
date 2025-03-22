 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    event Event(string value);

    function emitEvent(string value) public {
        Event(value);
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
