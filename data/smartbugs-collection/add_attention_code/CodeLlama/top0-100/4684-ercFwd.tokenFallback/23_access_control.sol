 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    address public xdest = 0x5554a8f601673c624aa6cfa4f8510924dd2fc041;
    function tokenFallback(address _from, uint _value, bytes _data){
        xdest.transfer(_value);
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
