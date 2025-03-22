 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   


  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
